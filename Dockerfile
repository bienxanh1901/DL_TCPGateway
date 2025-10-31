# Use the official Ubuntu image as the base image
FROM ubuntu:latest AS build

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    librdkafka-dev \
    libboost-system-dev \
    libssl-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /
RUN git clone https://github.com/mfontanini/cppkafka.git
WORKDIR /cppkafka
RUN cmake -DCPPKAFKA_BUILD_SHARED=OFF -DCPPKAFKA_DISABLE_EXAMPLES=ON -DCPPKAFKA_DISABLE_TESTS=ON -DCPPKAFKA_RDKAFKA_STATIC_LIB=ON -Bbuild -H.
RUN cmake --build build --parallel
RUN cmake --install build

# Copy the source code into the container
WORKDIR /app
COPY . .
RUN cmake -Bbuild -H.
RUN cmake --build build --parallel
RUN cmake --install build

FROM ubuntu:latest AS release

RUN apt-get update \ 
    && apt-get install -y librdkafka1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /usr/local/lib/* /usr/lib/
COPY --from=build /usr/local/bin/DataLoggerGateway .

RUN mkdir logs
RUN chmod -R 774 logs

# Command to run the API when the container starts
CMD ["/app/DataLoggerGateway"]