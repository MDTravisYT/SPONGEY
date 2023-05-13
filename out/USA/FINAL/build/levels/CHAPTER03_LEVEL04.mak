# print  <<eot
.PHONY : makeCHAPTER03_LEVEL04 cleanCHAPTER03_LEVEL04

makeCHAPTER03_LEVEL04:	CHAPTER03_LEVEL04_LVL

cleanCHAPTER03_LEVEL04:	cleanCHAPTER03_LEVEL04_LVL

CHAPTER03_LEVEL04_IN  :=	$(LEVELS_IN_DIR)/CHAPTER03/LEVEL04/LEVEL04.mex
CHAPTER03_LEVEL04_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER03_LEVEL04.lvl
CHAPTER03_LEVEL04_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER03_LEVEL04.tex

cleanCHAPTER03_LEVEL04_LVL :
	$(RM) -f $(CHAPTER03_LEVEL04_OUT) $(CHAPTER03_LEVEL04_TEX)
CHAPTER03_LEVEL04_LVL :	$(CHAPTER03_LEVEL04_IN)

$(CHAPTER03_LEVEL04_OUT) : $(CHAPTER03_LEVEL04_IN)
	@$(MKLEVEL) $(CHAPTER03_LEVEL04_IN) -o:$(CHAPTER03_LEVEL04_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER03_LEVEL04_OPTS)

