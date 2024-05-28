image:
	@docker build -f dockerfiles/dev -t httpino-dev-image .
.PHONY: image

cmake: image
	@docker run -it --rm \
		-w /httpino/build/ \
		-v $(PWD)/build:/httpino/build \
		-v $(PWD)/CMakeLists.txt:/httpino/CMakeLists.txt \
		-v $(PWD)/src:/httpino/src \
		httpino-dev-image \
		sh -c "\
			cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=1 \
				-D CMAKE_TOOLCHAIN_FILE=Arduino-CMake-Toolchain/Arduino-toolchain.cmake \
				-D ARDUINO_INSTALL_PATH=/root/.arduino15 \
				-D ARDUINO_ENABLE_PACKAGE_MANAGER=ON \
				-D ARDUINO_PLATFORM=arduino.renesas_uno .. && \
			rm -f /httpino/compile_commands.json \
		"
.PHONY: cmake

build: cmake
	@docker run -it --rm \
		-w /httpino/build/ \
		-v $(PWD)/build:/httpino/build \
		-v $(PWD)/CMakeLists.txt:/httpino/CMakeLists.txt \
		-v $(PWD)/src:/httpino/src \
		httpino-dev-image \
		sh -c "\
			make \
		"
.PHONY: build

ssh:
	@docker run --rm -it \
		-v $(PWD)/src/:/httpino/src \
		-v $(PWD)/test/:/httpino/test \
		-w /httpino/ httpino-dev-image bash
.PHONY: ssh

format:
	@docker run --rm -it -v $(PWD)/src/:/httpino/src \
		-v $(PWD)/test/:/httpino/test \
		-w /httpino/ \
		httpino-dev-image \
		sh -c "find src/ test/src/ test/include/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=Chromium -i"
.PHONY: format

check-format:
	@docker run --rm -it \
		-v $(PWD)/src/:/httpino/src \
		-v $(PWD)/test/:/httpino/test \
		-w /httpino/ \
		httpino-dev-image \
		sh -c "find src/ test/src/ test/include/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=Chromium --dry-run -Werror"
.PHONY: check-format

cmake_test: image
	@docker run -it --rm \
		-w /httpino/test/build/ \
		-v $(PWD)/test/build:/httpino/test/build \
		-v $(PWD)/test/CMakeLists.txt:/httpino/test/CMakeLists.txt \
		-v $(PWD)/src:/httpino/src \
		-v $(PWD)/test/src:/httpino/test/src \
		-v $(PWD)/test/include:/httpino/test/include \
		-v $(PWD)/test/external:/httpino/test/external \
		httpino-dev-image \
		sh -c " \
			cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=1 .. && \
			rm -f /httpino/test/compile_commands.json \
		"
.PHONY: cmake_test

test: cmake_test
	@docker run -it --rm \
		-w /httpino/test/build/ \
		-v $(PWD)/test/build:/httpino/test/build \
		-v $(PWD)/test/CMakeLists.txt:/httpino/test/CMakeLists.txt \
		-v $(PWD)/src:/httpino/src \
		-v $(PWD)/test/src:/httpino/test/src \
		-v $(PWD)/test/include:/httpino/test/include \
		-v $(PWD)/test/external:/httpino/test/external \
		httpino-dev-image \
		sh -c " \
			make && \
			./test \
		"
.PHONY: test

verify: image build check-format test
.PHONY: verify

# Starts a container with a neovim development environment ready to use
vim: cmake cmake_test
	@docker build -f dockerfiles/dev-vim -t smart-fluid-flow-meter-httpino-dev-vim-image .
	@docker run --rm -it \
		-v $(PWD)/assets:/httpino/assets \
		-v $(PWD)/build:/httpino/build \
		-v $(PWD)/CMakeLists.txt:/httpino/CMakeLists.txt \
		-v $(PWD)/README.md:/httpino/README.md \
		-v $(PWD)/Makefile:/httpino/Makefile \
		-v $(PWD)/src:/httpino/src \
		-v $(PWD)/test:/httpino/test \
		-v $(PWD)/dockerfiles:/httpino/dockerfiles \
		-v $(PWD)/dev-environments/vim/tmp:/root/.local/share/nvim \
		-w /httpino/ \
		smart-fluid-flow-meter-httpino-dev-vim-image \
		sh -c " \
			rm -f /httpino/test/compile_commands.json && \
			ln -s /httpino/build/compile_commands.json /httpino/ && \
			ln -s /httpino/test/build/compile_commands.json /httpino/test/ && \
			nvim \
		"
.PHONY: vim
