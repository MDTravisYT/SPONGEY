# print  <<eot
.PHONY : makeCHAPTER05_LEVEL01 cleanCHAPTER05_LEVEL01

makeCHAPTER05_LEVEL01:	CHAPTER05_LEVEL01_LVL

cleanCHAPTER05_LEVEL01:	cleanCHAPTER05_LEVEL01_LVL

CHAPTER05_LEVEL01_IN  :=	$(LEVELS_IN_DIR)/CHAPTER05/LEVEL01/LEVEL01.mex
CHAPTER05_LEVEL01_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER05_LEVEL01.lvl
CHAPTER05_LEVEL01_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER05_LEVEL01.tex

cleanCHAPTER05_LEVEL01_LVL :
	$(RM) -f $(CHAPTER05_LEVEL01_OUT) $(CHAPTER05_LEVEL01_TEX)
CHAPTER05_LEVEL01_LVL :	$(CHAPTER05_LEVEL01_IN)

$(CHAPTER05_LEVEL01_OUT) : $(CHAPTER05_LEVEL01_IN)
	@$(MKLEVEL) $(CHAPTER05_LEVEL01_IN) -o:$(CHAPTER05_LEVEL01_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER05_LEVEL01_OPTS)

