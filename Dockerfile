FROM gcc:9 as build
RUN mkdir -p /out/etc/rescached /out/var/cache/rescached /out/usr/sbin /out/lib/x86_64-linux-gnu/
RUN cd /out && ln -s lib lib64
RUN touch /out/etc/hosts

COPY . /rescached/
WORKDIR rescached/src
RUN git submodule init --
RUN git submodule update --
RUN make
RUN cp build/rescached /out/usr/sbin/

COPY rescached-docker.cfg /out/etc/rescached/rescached.cfg


FROM scratch
COPY --from=busybox:glibc /lib/ld-linux-x86-64.so.2 /lib/libc.so.6 /lib/libpthread.so.0 /lib/
COPY --from=build /out /
ENTRYPOINT [ "/usr/sbin/rescached", "/etc/rescached/rescached.cfg" ]