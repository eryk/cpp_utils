FROM centos:centos7

RUN yum -y update
RUN yum -y install scl-utils openssh-server openssh-clients vim git wget rsync tar make gcc gdb perl pcre-devel zlib-devel automake devtoolset-9-gdb centos-release-scl
RUN yum install -y devtoolset-9-gcc-*
RUN echo "source scl_source enable devtoolset-9" >> /etc/bashrc
RUN source /etc/bashrc

WORKDIR /root/software
RUN wget -q --no-check-certificate https://www.openssl.org/source/openssl-1.1.1g.tar.gz && tar -zxvf openssl-1.1.1g.tar.gz \
    && cd openssl-1.1.1g && ./config --prefix=/usr --openssldir=/etc/ssl --libdir=lib no-shared zlib-dynamic && make && make install
RUN wget -q --no-check-certificate https://cmake.org/files/v3.17/cmake-3.17.0.tar.gz \
    && tar -zxvf cmake-3.17.0.tar.gz && cd cmake-3.17.0 && ./bootstrap && make && make install && rm -rf /root/software

RUN ssh-keygen -P "" -t rsa -f /etc/ssh/ssh_host_rsa_key && ssh-keygen -P "" -t ecdsa -f /etc/ssh/ssh_host_ecdsa_key \
    && ssh-keygen -P "" -t ed25519 -f /etc/ssh/ssh_host_ed25519_key

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