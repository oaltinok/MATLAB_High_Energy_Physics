# ==============================================================================
#
# Makefile for NTupleAnalysis Package
# 	Statistical Data Analysis Package for CCProtonPi0
#	Author: Ozgur Altinok
#
# ==============================================================================

# Main File and its executable
MAINEXE = main.exe
MAINCPP = main.cpp
MINUITFUNCSCPP = src/Minuit_Functions.cpp
MINUITFUNCSWCPP = src/Minuit_Functions_W.cpp
MAINFUNCSCPP = src/Main_Functions.cpp
ROOTFITTERQSQ = src/ROOT_Fitter_QSq.cpp
ALLMAINCPP = $(MAINCPP) $(MINUITFUNCSCPP) $(MINUITFUNCSWCPP) $(MAINFUNCSCPP) $(ROOTFITTERQSQ)

# Class: Base Class
NTUPLEANALYSISCPP = Classes/NTupleAnalysis/CCProtonPi0_NTupleAnalysis.cpp

# Class: Plotter
PLOTTERMACROSCPP = Classes/Plotter/CCProtonPi0_Plotter_Macros.cpp
PLOTTERCPP = Classes/Plotter/CCProtonPi0_Plotter.cpp
UNFOLDINGSTUDYCPP = Classes/Plotter/CCProtonPi0_Plotter_UnfoldingStudy.cpp
SYSTEMATICSCPP = Classes/Plotter/CCProtonPi0_Plotter_Systematics.cpp
GENIETUNINGCPP = Classes/Plotter/CCProtonPi0_Plotter_GENIE_Tuning.cpp
WFITCPP = Classes/Plotter/CCProtonPi0_Plotter_W_Fit.cpp
QSQCPP = Classes/Plotter/CCProtonPi0_Plotter_QSq.cpp
PAPERCPP = Classes/Plotter/CCProtonPi0_Plotter_Paper.cpp
SUPPLEMENTCPP = Classes/Plotter/CCProtonPi0_Plotter_Supplement.cpp
ALLPLOTTERCPP = $(PLOTTERMACROSCPP) $(PLOTTERCPP) $(UNFOLDINGSTUDYCPP) $(SYSTEMATICSCPP) $(GENIETUNINGCPP) $(WFITCPP) $(QSQCPP) $(PAPERCPP) $(SUPPLEMENTCPP)

# Class: Analyzer
ANALYZERCPP = Classes/Analyzer/CCProtonPi0_Analyzer.cpp
ANALYZERDEFAULTCPP = Classes/Analyzer/CCProtonPi0_Analyzer_Default.cpp
ANALYZERSYSTEMATICSCPP = Classes/Analyzer/CCProtonPi0_Analyzer_Systematics.cpp
ALLANALYZERCPP = $(ANALYZERCPP) $(ANALYZERDEFAULTCPP) $(ANALYZERSYSTEMATICSCPP)

# Class: CrossSection
CROSSSECTIONCPP = Classes/CrossSection/CCProtonPi0_CrossSection.cpp
CROSSSECTIONSTYLECPP = Classes/CrossSection/CCProtonPi0_CrossSection_Style.cpp
ALLCROSSSECTIONCPP = $(CROSSSECTIONCPP) $(CROSSSECTIONSTYLECPP)

# Class: Interaction, Particle and Particle SubClasses
INTERACTIONCPP = Classes/Interaction/CCProtonPi0_Interaction.cpp
PARTICLECPP = Classes/Particle/CCProtonPi0_Particle.cpp 
MUONCPP = Classes/Muon/CCProtonPi0_Muon.cpp
PROTONCPP = Classes/Proton/CCProtonPi0_Proton.cpp
PIONCPP = Classes/Pion/CCProtonPi0_Pion.cpp
PI0BLOBCPP = Classes/Pi0Blob/CCProtonPi0_Pi0Blob.cpp
ALLPARTICLESCPP = $(INTERACTIONCPP) $(PARTICLECPP) $(MUONCPP) $(PROTONCPP) $(PIONCPP) $(PI0BLOBCPP)

# Tools for Detailed Studies
PIDTOOLCPP = Classes/PIDTool/CCProtonPi0_PIDTool.cpp
BACKGROUNDTOOLCPP = Classes/BackgroundTool/CCProtonPi0_BackgroundTool.cpp
MICHELTOOLCPP = Classes/MichelTool/CCProtonPi0_MichelTool.cpp
SIDEBANDTOOLCPP = Classes/SideBandTool/CCProtonPi0_SideBandTool.cpp
ALLTOOLCPP = $(BACKGROUNDTOOLCPP) $(SIDEBANDTOOLCPP)

# Other Helper Classes
QSQFITTER = Classes/QSqFitter/CCProtonPi0_QSqFitter.cpp
COUNTERCPP = Classes/Counter/CCProtonPi0_Counter.cpp
BINLISTCPP = Classes/BinList/CCProtonPi0_BinList.cpp
CUTLISTCPP = Classes/CutList/CCProtonPi0_CutList.cpp
SINGLEBINCPP = Classes/SingleBin/CCProtonPi0_SingleBin.cpp
CUTCPP = Classes/Cut/CCProtonPi0_Cut.cpp
CUTSTATCPP = Classes/Cut/CCProtonPi0_CutStat.cpp
RANDNUMGENERATORCPP = Classes/RandNumGenerator/CCProtonPi0_RandNumGenerator.cpp
BCKGCONSTRAINERCPP = Classes/BckgConstrainer/CCProtonPi0_BckgConstrainer.cpp
ALLOTHERCPP = $(BINLISTCPP) $(SINGLEBINCPP) $(CUTLISTCPP) $(CUTCPP) $(CUTSTATCPP) $(RANDNUMGENERATORCPP) $(COUNTERCPP) $(BCKGCONSTRAINERCPP) $(QSQFITTER)

# ALL Classes Required for the Package
ALLCPP = $(ALLMAINCPP) $(NTUPLEANALYSISCPP) $(ALLANALYZERCPP) $(ALLCROSSSECTIONCPP) $(ALLPARTICLESCPP) $(ALLTOOLCPP) $(ALLOTHERCPP) $(ALLPLOTTERCPP)

# PlotUtils from MINERvA Framework
INCLUDES += -I$(PLOTUTILSROOT)/ -I$(UNFOLDUTILSROOT)/
LDLIBS += -L$(PLOTUTILSROOT)/$(CMTCONFIG) -lplotutils -L$(UNFOLDUTILSROOT)/$(CMTCONFIG) -lUnfoldUtils

# ------------------------------------------------------------------------------
# Commands and Flags
# ------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -Wall -Wextra -std=c++0x
ROOTFLAGS = `root-config --glibs --cflags`
RM = rm -fv

SOURCES = $(ALLCPP)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = $(MAINEXE)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(ROOTFLAGS) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJECTS) $(LDLIBS) 

.cpp.o:
	$(CC) $(ROOTFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean: 
	$(RM) $(MAINEXE) $(OBJECTS)

