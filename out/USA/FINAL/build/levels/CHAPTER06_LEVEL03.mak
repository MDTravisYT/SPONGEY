# print  <<eot
.PHONY : makeCHAPTER06_LEVEL03 cleanCHAPTER06_LEVEL03

makeCHAPTER06_LEVEL03:	CHAPTER06_LEVEL03_LVL

cleanCHAPTER06_LEVEL03:	cleanCHAPTER06_LEVEL03_LVL

CHAPTER06_LEVEL03_IN  :=	$(LEVELS_IN_DIR)/CHAPTER06/LEVEL03/LEVEL03.mex
CHAPTER06_LEVEL03_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER06_LEVEL03.lvl
CHAPTER06_LEVEL03_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER06_LEVEL03.tex

cleanCHAPTER06_LEVEL03_LVL :
	$(RM) -f $(CHAPTER06_LEVEL03_OUT) $(CHAPTER06_LEVEL03_TEX)
CHAPTER06_LEVEL03_LVL :	$(CHAPTER06_LEVEL03_IN)

$(CHAPTER06_LEVEL03_OUT) : $(CHAPTER06_LEVEL03_IN)
	@$(MKLEVEL) $(CHAPTER06_LEVEL03_IN) -o:$(CHAPTER06_LEVEL03_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER06_LEVEL03_OPTS)
