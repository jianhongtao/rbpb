#include <time.h>
#include <stdlib.h>

#include "NtripAuth.h"


//length of "Authorization-Info: nextnonce"
#define AUTH_INFO_LABLE_LEN    (29)

// parse request line
#define PARSE_REQUEST_LIEN(p, pos, n, head)\
{\
    do\
    {\
        /*get method , URL , version ; splited by '\0'; */ \
        if (*(p + pos) != ' '){\
            head[pos] = *(p + pos); \
        }else{\
            head[pos] = '\0'; n++; \
        }pos++; \
    } while (*(p + pos) != '\r' && *(p + pos + 1) != '\n'); \
    head[pos] = '\0'; pos += 2; \
}

#define  PARSE_REQUEST_HEADER(keylen, p, pos, j , out)\
{\
    pos += keylen; \
    while (*(p + pos) == ' ') pos++; /*jump space*/ \
    do\
    {\
        out[j] = *(p + pos); \
        pos++; j++; \
    } while (*(p + pos) != '\r' && *(p + pos + 1) != '\n'); \
    out[j] = '\0'; pos += 2; \
}

#define PARSE_AUTH_TYPE(keylen, p, pos, j, out, type)\
{\
        pos += keylen;\
        while (*(p + pos) == ' ') pos++;\
        do{\
            if (*(p + pos) != ' '){\
                out[j] = *(p + pos);\
            }\
            else{\
                out[j] = '\0';\
                break;\
            }\
            pos++; j++;\
        } while (true);\
        if (!memcmp(out, "Digest", 6)){\
            type = auth_digest; \
        }\
        else if (!memcmp(out, "Basic", 5)){\
            type = auth_basic;\
        }\
        else{\
            type = auth_unknown;\
        }\
}

#define PARSE_AUTH_INFO(keylen, p, j, pos, flag, v)\
{\
    pos += keylen; \
    while (*(p + pos) == ' ') pos++; /*jump space.*/\
    /*while (*(p + pos) != ',' || *(p+pos)!= ' ');*/\
    do{\
        if (*(p + pos) != '"'){\
            v[j++] = *(p + pos); \
        }\
       else{\
            if (flag){\
                if (*(p + pos + 1) == ',') pos++; \
                break; \
            }\
            flag = true; \
        }pos++; \
    } while (true); v[j] = '\0'; \
    pos += 1; while (*(p + pos) == ' ') pos++; /*jump space.*/\
}


const unsigned char HexStr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'A', 'B', 'C', 'D', 'E', 'F',
'a', 'b', 'c', 'd', 'e', 'f'
};

char *GetRandom(char*p, int N, int seed)
{
    srand(seed);
    int i = 0, k = 0, j = 0, random;
    for (i = 0; i < N; i++)
    {
        random = rand();
        k = random % 22;
        p[j++] = HexStr[k];
    }
    p[j] = '\0';
    return p;
}

// 16bit unsigned int to binary
void D2B(const unsigned int d, char b[])
{
    int j = 7;
    for (int i = 0; i < 8; i++)
    {
        if (d & (1 << i))
            b[j] = '1';
        else
            b[j] = '0';

        j--;
    }
}

NtripAuth::NtripAuth():m_UserInfoMap(NULL)
{

}

NtripAuth::~NtripAuth()
{
    if (m_UserInfoMap)
    {
        delete m_UserInfoMap;
        m_UserInfoMap = NULL;
    }
}

int NtripAuth::ParseNtripRequest(const char *buf, int len, int *method, AuthResponse_s *pAuthInfo)
{
    char *p = (char*)buf;
    int n = 0, pos = 0, j = 0;
    char head[128], out[64];
    int authType;
    bool flag = false;

    // parse request line
    PARSE_REQUEST_LIEN(p, pos, n ,head);

    if (n != 2)
    {
        LOG("error : invalid request line\n");
        return -1;
    }
    if (!memcmp(head, "GET", 3))
    {
        *method = method_get;
    }
    else if (!memcmp(head, "POST", 4))
    {
        *method = method_post;
    }
    else
    {
        LOG("shit : unknown method for this verion\n");
        return -1;
    }

    //parse request header
    do
    {
        j = 0;
        if (!memcmp(p + pos, "Host", 4))
        {
            PARSE_REQUEST_HEADER(5, p, pos, j, out);
            goto end;
        }
        else if (!memcmp(p + pos, "Date", 4))
        {
            PARSE_REQUEST_HEADER(5, p, pos, j, out);
            goto end;
        }
        else if (!memcmp(p + pos, "Content-Type", 12))
        {
            PARSE_REQUEST_HEADER(13, p, pos, j, out);
            goto end;
        }
        else if (!memcmp(p + pos, "Content-Length", 14))
        {
            PARSE_REQUEST_HEADER(15, p, pos, j, out);
            goto end;
        }
        else if (!memcmp(p + pos, "Connection", 10))
        {
            PARSE_REQUEST_HEADER(11, p, pos, j, out);
            goto end;
        }
        else if (!memcmp(p + pos, "WWW-Authenticate", 16))
        {
            PARSE_AUTH_TYPE(17, p, pos, j, out, authType);
            pAuthInfo->type = authType;

            if (authType == auth_unknown)
            {
                LOG("warning: unknown authentication type\n");
                return -1;
            }
  //          else if (authType != auth_digest)
  //          {
   //
   //         }

            // get authenticaion detail info
            do
            {
                while (*(p + pos) == ' ') pos++;
                do
                {
                    j = 0;
                    flag = false;
                    if (!memcmp(p + pos, "realm", 5))
                    {
                        PARSE_AUTH_INFO(6, p, j, pos, flag, pAuthInfo->realm);
                    }
                    else if (!memcmp(p + pos, "qoq", 3))
                    {
                        PARSE_AUTH_INFO(4, p, j, pos, flag, pAuthInfo->qoq);
                    }
                    else if (!memcmp(p + pos, "nonce", 5))
                    {
                        PARSE_AUTH_INFO(6, p, j, pos, flag, pAuthInfo->nonce);
                    }
                    else if (!memcmp(p + pos, "opaque", 6))
                    {
                        PARSE_AUTH_INFO(7, p, j, pos, flag, pAuthInfo->opaque);
                    }
                    else if (!memcmp(p + pos, "uri", 3))
                    {
                        PARSE_AUTH_INFO(4, p, j, pos, flag, pAuthInfo->uri);
                    }
                    else if (!memcmp(p + pos, "algorithm", 9))
                    {
                        PARSE_AUTH_INFO(10, p, j, pos, flag, pAuthInfo->algorithm);
                    }
                    else if (!memcmp(p + pos, "username", 8))
                    {
                        PARSE_AUTH_INFO(9, p, j, pos, flag, pAuthInfo->username);
                    }
                    else if (!memcmp(p + pos, "cnonce", 6))
                    {
                        PARSE_AUTH_INFO(7, p, j, pos, flag, pAuthInfo->cnonce);
                    }
                    else if (!memcmp(p + pos, "nc", 2))
                    {
                        PARSE_AUTH_INFO(3, p, j, pos, flag, pAuthInfo->nc);
                    }
                    else if (!memcmp(p + pos, "response", 8))
                    {
                        PARSE_AUTH_INFO(9, p, j, pos, flag, pAuthInfo->response);
                    }
                    else
                    {
                        LOG("warning: unkown authenticate lable\n");
                        return -1;
                    }
                } while (*(p + pos) != '\r' && *(p + pos + 1) != '\n');
                pos += 2;
                goto end;
            } while (true);
        }
    end:
        if (*(p + pos) == '\r' && *(p + pos + 1) == '\n')
            return 0;

    } while (true);

    //never come to here.
    return 0;
}

int NtripAuth::Encode401Response(char *buf, int bufLen)
{
    char date[64];
    char nonce[64];
    char opaque[64];

    int  seed = (unsigned)time(NULL);

    GetRandom(nonce, 32, seed);
    GetRandom(opaque, 32, seed + 1);

    struct tm *newtime;
    time_t ltime;
    time(&ltime);
    newtime = gmtime(&ltime);
    strftime(date, 128, "%a, %d %b %Y %H:%M:%S GMT", newtime);

    int len = sprintf(buf,
                        "HTTP/1.1 401 Unauthorized\r\n"
                        "Server: %s\r\n"
                        "Date: %s\r\n"
                        "Content-Length: %d\r\n"
                        "Connection: %s\r\n"
                        "WWW-Authenticate: Digest realm=\"%s\",qoq=\"%s\",nonce=\"%s\",opaque=\"%s\"\r\n\r\n"
                        ,
                        "bdStar@com",
                        date,
                        0,
                        "close",
                        "www.bdSatr@123.com",
                        "auth,auth-int",
                        nonce,
                        opaque
                        );
    buf[len] = '\0';
    return len;
}


int NtripAuth::VerifyAuthRequest(AuthResponse_s *pAuthInfo, const char *passwd)
{
    char *nonce    = pAuthInfo->nonce;
    char* opaque   = pAuthInfo->opaque;
    char* realm    = pAuthInfo->realm;
    char *cnonce   = pAuthInfo->cnonce;
    char *uri      = pAuthInfo->uri;
    char *username = pAuthInfo->username;
    char *nc	   = pAuthInfo->nc;

    //D2B(1, nc);
    //nc[8] = '\0';

    char A1[128], A2[128], A3[128], HD[128];
    // response : MD5£¨HA1:HA2:HA3
    MD5_CTX md5;

    //HA1
    int a1 = sprintf(A1, "%s:%s:%s", username, realm, passwd);
    A1[a1] = '\0';
    unsigned char HA1[17];
    MD5Init(&md5);
    MD5Update(&md5, (unsigned char*)A1, a1);
    MD5Final(&md5, HA1);
    HA1[16] = '\0';

    //HA2
    int a2 = sprintf(A2, "%s", nonce);
    //nonce:nc:cnonce:qop
    //int a2 = sprintf(A1, "%s:%s:%s:%s", nonce);
    A2[a2] = '\0';
    unsigned char HA2[17];
    MD5Init(&md5);
    MD5Update(&md5, (unsigned char*)A2, a2);
    MD5Final(&md5, HA2);
    HA2[16] = '\0';

    //HA3
    //method:uri
    int a3 = sprintf(A3, "%s:%s", "GET", uri);
    A3[a3] = '\0';

    unsigned char HA3[17];
    MD5Init(&md5);
    MD5Update(&md5, (unsigned char*)A3, a3);
    MD5Final(&md5, HA3);
    HA3[16] = '\0';

    //reponse
    //HA1£ºHA2£ºHA3
    unsigned char response[17];
    int d = sprintf(HD, "%s:%s:%s", HA1, HA2, HA3);
    HD[d] = '\0';
    MD5Init(&md5);
    MD5Update(&md5, (unsigned char*)HD, d);
    MD5Final(&md5, response);
    response[16] = '\0';

    if (!memcmp(response, pAuthInfo->response, 16))
    {
        return status_200;
    }

    return status_401;
}

int  NtripAuth::EncodeAuth200OkResponse(char *buf, int bufLen, int staut)
{
    int len = 0;
    char nonce[64];

    int  seed = (unsigned)time(NULL);
    GetRandom(nonce, 32, seed);

    len =   sprintf(buf,
                    "HTTP/1.1 %d OK\r\n"
                    "Authorization-Info: nextnonce=\"%s\"\r\n"
                    "Content-Length: %d\r\n"
                    "Connection: %s\r\n\r\n"
                    ,
                    staut,
                    nonce,
                    0,
                    "close"
                    );

    buf[len] = '\0';

    return len;
}

int NtripAuth::InitUserInfoMap(const char* pConfFile)
{
    return 0;
}
