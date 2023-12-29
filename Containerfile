FROM fedora:latest
WORKDIR /opt/workdir

RUN sudo dnf install -y \
	cmake \
	libX11-devel \
	libXrandr-devel \
	clang \
	ninja-build

CMD cmake -B target/release -D CMAKE_BUILD_TYPE=Release -G "Ninja" && cmake --build target/release -j$(nproc)
