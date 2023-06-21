# Base image
FROM ubuntu:latest

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    python3 \
    python3-pip

# Set the working directory
WORKDIR /app

# Copy the C++ source code and bash files
COPY test /app/test
COPY src/cpp /app/src/cpp
COPY data/csv /app/data/csv

# Copy the Python source code and requirements file
COPY src/automation /app/src/automation
COPY docker/requirements.txt /app

# Install Python dependencies
RUN pip3 install -r requirements.txt

# Build and compile the C++ code
RUN cd /app/src/cpp && g++ main.cpp -o program

# Set the entry point
ENTRYPOINT ["/app/test/run.sh"]
