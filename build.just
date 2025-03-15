[group('build')]
default: build

[group('build')]
init:
  echo Creating needed folders...
  mkdir -p build

[group('build')]
[working-directory: 'build']
generate: init
    @echo 'Generating cmake...'
    cmake ..

[group('build')]
[working-directory: 'build']
build: generate
    @echo 'Building ...'
    cmake --build .

[group('build')]
build_run: build run

[group('build')]
run:
    @echo 'Running the GUI'
    ./build/src/GUI/gui

[group('build')]
[confirm]
clean:
    rm build -rf

