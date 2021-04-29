FROM ubuntu:18.04

ADD sources.list /etc/apt/
ADD pip.conf ~/.pip/
ADD Shanghai /etc/localtime

RUN apt-get update && apt-get install -y \
        ssh \
        dmidecode \
        build-essential \
        libssl-dev \
        gcc \
        g++ \
        gdb \
        gdbserver \
        cmake \
        rsync \
        python \
        vim \
        automake \
        openssh-client \
        openssh-server \
    && apt-get clean \

WORKDIR /root/software
RUN wget -q --no-check-certificate https://cmake.org/files/v3.16/cmake-3.16.9.tar.gz \
    && tar -zxvf cmake-3.16.9.tar.gz && cd cmake-3.16.9 && ./bootstrap && make && make install && rm -rf /root/software

RUN mkdir /var/run/sshd
RUN echo "root:root123" | chpasswd

RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

# 暴露端口  22 for ssh server. 7777 for gdb server.
EXPOSE 22 7777
CMD ["/usr/sbin/sshd", "-D"]