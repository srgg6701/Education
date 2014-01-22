CXX=/usr/bin/g++
CXXFLAGS=-g
SRC_FILES = $(wildcard src/*.cpp)
SRC_AUXS  = $(filter-out src/main%.cpp,$(SRC_FILES))
SRC_MAINS = $(filter src/main%.cpp,$(SRC_FILES))

OBJ_FILES = $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES)) 
OBJ_AUXS  = $(patsubst src/%.cpp,obj/%.o,$(SRC_AUXS)) 
OBJ_MAINS = $(patsubst src/%.cpp,obj/%.o,$(SRC_MAINS)) 

ODIR=obj
SDIR=src
BDIR=bin
DDIR=data

#
# PROGRAM
#
all: dirs $(patsubst src/%.cpp,bin/%.out,$(SRC_MAINS))

dirs:
	mkdir -p $(ODIR) $(DDIR) $(BDIR)

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $(patsubst src/%.cpp,obj/%.o,$<) 

#All mains include everything (It is an example program, so I dont care)
$(BDIR)/%.out: $(OBJ_AUXS) $(ODIR)/%.o
	$(CXX) $(CXXFLAGS) $+ -o $@


#
# PLOTTING
#
PGEN   = scripts/pointgen.py
PLOTG  = scripts/gnuplot.sh
OUTD   = data
PSOUT  = plots.ps

plots: plot plotf

plot: all
	$(PGEN) -o $(OUTD)
	/bin/bash ${PLOTG}
	/bin/cp $(PSOUT) plotsint.ps

plotf: all
	$(PGEN) --float -o $(OUTD)
	/bin/bash ${PLOTG}
	/bin/cp $(PSOUT) plotsfloat.ps


#
# EXTRA
#
ctags:
	/usr/bin/ctags -R .

clean:
	find . -iname "*.o" -exec rm -f {} \;
	rm -f data/*
	rm -f bin/*
	rm -f *.ps


