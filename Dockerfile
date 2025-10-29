# Use the official Ubuntu image as the base image
FROM ubuntu:latest AS build

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Copy the source code into the container
WORKDIR /app
COPY . .
RUN cmake -Bbuild -H.
RUN cmake --build build --parallel
RUN cmake --install build

FROM ubuntu:latest AS release

RUN apt-get update && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /usr/local/bin/QCVNCloudGateway .

RUN mkdir logs
RUN chmod -R 774 logs

# Command to run the API when the container starts
CMD ["/app/QCVNCloudGateway"]