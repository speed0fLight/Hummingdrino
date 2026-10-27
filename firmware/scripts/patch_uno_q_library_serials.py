Import("env") # type: ignore

from pathlib import Path


libraries = (
    (
        "FastIMU",
        Path("src/sensors/F_HMC5883L.cpp"),
    ),
    (
        "arduino-px4flow-i2c",
        Path("PX4Flow.cpp"),
    ),
)
dependency_dir = Path(env.subst("$PROJECT_LIBDEPS_DIR")) / env.subst("$PIOENV") # type: ignore

for library, relative_path in libraries:
    library_source = dependency_dir / library / relative_path
    source = library_source.read_text()
    if "Serial." in source:
        library_source.write_text(source.replace("Serial.", "Serial1."))
    elif "Serial1." not in source:
        raise RuntimeError(f"Expected serial diagnostics not found in {library_source}")
