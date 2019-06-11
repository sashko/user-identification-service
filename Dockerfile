FROM ubuntu:18.04

# Install core dependencies
RUN apt-get update && \
    apt-get install -qq -y --option=Dpkg::Options::=--force-confnew \
        build-essential \
        gcc \
        git \
        locales \
        meson \
        ninja-build \
        python \
        sudo \
        wget \
        xz-utils
RUN rm -rf /var/lib/apt/lists/*

# Set up locale
RUN /usr/sbin/locale-gen en_US.UTF-8
RUN localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.UTF8

# Replace dash with bash
RUN ln -sf /bin/bash /bin/sh

RUN useradd -U -m user
RUN usermod --uid 1003 user
RUN groupmod --gid 1003 user
RUN adduser user sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER user
WORKDIR /home/user/
CMD /bin/bash
