test-outputs: test-outputs.c
	gcc -o test-outputs test-outputs.c -liobb

test-inputs: test-inputs.c
	gcc -o test-inputs test-inputs.c -liobb

pb-test-inputs: pb-test-inputs.c
	gcc -o pb-test-inputs pb-test-inputs.c -liobb

pb-test-outputs: pb-test-outputs.c
	gcc -o pb-test-outputs pb-test-outputs.c -liobb

all: test-outputs test-inputs pb-test-inputs pb-test-outputs

clean:
	rm -rf test-inputs test-outputs pb-test-inputs pb-test-outputs

