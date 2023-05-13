# print  <<eot
.PHONY : makeCHAPTER04_LEVEL01 cleanCHAPTER04_LEVEL01

makeCHAPTER04_LEVEL01:	CHAPTER04_LEVEL01_LVL

cleanCHAPTER04_LEVEL01:	cleanCHAPTER04_LEVEL01_LVL

CHAPTER04_LEVEL01_IN  :=	$(LEVELS_IN_DIR)/CHAPTER04/LEVEL01/LEVEL01.mex
CHAPTER04_LEVEL01_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER04_LEVEL01.lvl
CHAPTER04_LEVEL01_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER04_LEVEL01.tex

cleanCHAPTER04_LEVEL01_LVL :
	$(RM) -f $(CHAPTER04_LEVEL01_OUT) $(CHAPTER04_LEVEL01_TEX)
CHAPTER04_LEVEL01_LVL :	$(CHAPTER04_LEVEL01_IN)

$(CHAPTER04_LEVEL01_OUT) : $(CHAPTER04_LEVEL01_IN)
	@$(MKLEVEL) $(CHAPTER04_LEVEL01_IN) -o:$(CHAPTER04_LEVEL01_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER04_LEVEL01_OPTS)
