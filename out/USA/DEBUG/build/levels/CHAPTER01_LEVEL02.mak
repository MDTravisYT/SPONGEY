# print  <<eot
.PHONY : makeCHAPTER01_LEVEL02 cleanCHAPTER01_LEVEL02

makeCHAPTER01_LEVEL02:	CHAPTER01_LEVEL02_LVL

cleanCHAPTER01_LEVEL02:	cleanCHAPTER01_LEVEL02_LVL

CHAPTER01_LEVEL02_IN  :=	$(LEVELS_IN_DIR)/CHAPTER01/LEVEL02/LEVEL02.mex
CHAPTER01_LEVEL02_OUT :=	$(LEVELS_OUT_DIR)/CHAPTER01_LEVEL02.lvl
CHAPTER01_LEVEL02_TEX :=	$(LEVELS_OUT_DIR)/CHAPTER01_LEVEL02.tex

cleanCHAPTER01_LEVEL02_LVL :
	$(RM) -f $(CHAPTER01_LEVEL02_OUT) $(CHAPTER01_LEVEL02_TEX)
CHAPTER01_LEVEL02_LVL :	$(CHAPTER01_LEVEL02_IN)

$(CHAPTER01_LEVEL02_OUT) : $(CHAPTER01_LEVEL02_IN)
	@$(MKLEVEL) $(CHAPTER01_LEVEL02_IN) -o:$(CHAPTER01_LEVEL02_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(CHAPTER01_LEVEL02_OPTS)
