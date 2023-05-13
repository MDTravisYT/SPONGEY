# print  <<eot
.PHONY : makeCHAPTER01_LEVEL01 cleanCHAPTER01_LEVEL01

makeCHAPTER01_LEVEL01:	CHAPTER01_LEVEL01_LVL

cleanCHAPTER01_LEVEL01:	cleanCHAPTER01_LEVEL01_LVL

CHAPTER01_LEVEL01_IN  :=	$(LEVELS_IN_DIR)/CHAPTER01/LEVEL01/LEVEL01.mex
CHAPTER01_LEVEL01_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER01_LEVEL01.lvl
CHAPTER01_LEVEL01_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER01_LEVEL01.tex

cleanCHAPTER01_LEVEL01_LVL :
	$(RM) -f $(CHAPTER01_LEVEL01_OUT) $(CHAPTER01_LEVEL01_TEX)
CHAPTER01_LEVEL01_LVL :	$(CHAPTER01_LEVEL01_IN)

$(CHAPTER01_LEVEL01_OUT) : $(CHAPTER01_LEVEL01_IN)
	@$(MKLEVEL) $(CHAPTER01_LEVEL01_IN) -o:$(CHAPTER01_LEVEL01_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER01_LEVEL01_OPTS)
