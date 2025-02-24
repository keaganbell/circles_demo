targetname := clickable
targetsrc := src\\windows_$(targetname).cpp
targetexe := $(targetname).exe

compile_flags := /WL /nologo /Foobj\\ /Zi /O2 /Fdpdb\\compiler_$(targetname).pdb

linker_flags := /INCREMENTAL:NO /DEBUG
linker_flags += kernel32.lib user32.lib gdi32.lib opengl32.lib

builddir := bin\\debug
datadir := $(builddir)\\data
output := /OUT:$(builddir)\\$(targetexe) /PDB:pdb\\linker_$(targetname).pdb

shadersrcdir := ass\\shaders
shaderdir := $(datadir)\\shaders
shadersrc := $(wildcard ass/shaders/*)
shaders := $(patsubst ass/shaders/%,$(shaderdir)\\%,$(shadersrc))
defines += -DSHADER_DIR="\"data/shaders/\""

.PHONY: all
all: $(shaders) $(targetname)

.PHONY: $(targetname)
$(targetname): | obj pdb $(builddir)
	@cl $(compile_flags) $(defines) $(targetsrc) /link $(linker_flags) $(output)

pdb:
	@mkdir $@

obj:
	@mkdir $@

$(builddir): | bin
	@mkdir $@

bin:
	@mkdir $@

$(shaderdir)\\%.glsl: $(shadersrcdir)\\%.glsl | $(shaderdir)
	@copy $< $@

$(shaderdir): | $(datadir)
	@mkdir $@

$(datadir): | $(builddir)
	@mkdir $@

.PHONY: clean
clean:
	@del /Q pdb\\*
	@del /Q obj\\*
	@rmdir /s $(builddir)\\*
