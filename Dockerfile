FROM ubuntu:20.04

# タイムゾーンを対話的に問われることによるハングアップを阻止
ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update &&\
    apt-get install -y wget git cmake g++

RUN wget https://raw.githubusercontent.com/ETrobocon/etrobo/master/scripts/startetrobo -O ~/startetrobo && \
    sed -i -r 's/(\s*)sudo((\s+-[a-zA-Z0-9\-]+)*)?\s+/\1/g' ~/startetrobo && \
    chmod +x ~/startetrobo

# etrobo 環境のセットアップ
RUN git config --global user.name docker && \
    git config --global user.email example@example.com && \
    ~/startetrobo shell


ENV APP_NAME etrobocon2022
ENV COURSE l
ENV ADDITIONAL ""
ENTRYPOINT ["/bin/bash", "-c", "echo 'ln -s /tmp/${APP_NAME} ${ETROBO_ROOT}/workspace/${APP_NAME}; make ${COURSE} app=${APP_NAME} ${ADDITIONAL}' | ~/startetrobo shell"]
