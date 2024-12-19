FROM alpine:latest

RUN apk add --no-cache g++ git make

WORKDIR /app

RUN git clone https://github.com/karmichael228/parvpo1.git .

RUN g++ -o parallel_shell_sort parallel_shell_sort.cpp -fopenmp

CMD sh -c "./parallel_shell_sort > /host_output/result.txt"
