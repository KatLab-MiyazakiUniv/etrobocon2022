test:
	python -m unittest

run:
	python -m rear_camera --debug

format:
	python -m autopep8 -i -r rear_camera/ tests/

format-check:
	python -m pycodestyle rear_camera/ tests/
	python -m pydocstyle rear_camera/ tests/

clean:
	rm -rf ./debug