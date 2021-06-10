FROM caster_centos7:1.0 

WORKDIR /ppp/serv/bin

ENV SOFTNAME rbpb

COPY ./bin/$SOFTNAME ./$SOFTNAME

COPY ./cfg  ../cfg

RUN chmod 755 ./$SOFTNAME

EXPOSE 8001

CMD exec ./$SOFTNAME
