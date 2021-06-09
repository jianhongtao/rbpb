FROM bdps_run:1.0 

WORKDIR /ppp/serv/bin

ENV SOFTNAME rbpb

COPY ./bin/$SOFTNAME ./$SOFTNAME

RUN chmod 755 ./$SOFTNAME

EXPOSE 8001

CMD exec ./$SOFTNAME
