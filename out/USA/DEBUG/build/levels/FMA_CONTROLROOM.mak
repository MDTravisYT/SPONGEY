# print  <<eot
.PHONY : makeFMA_CONTROLROOM cleanFMA_CONTROLROOM

makeFMA_CONTROLROOM:	FMA_CONTROLROOM_LVL

cleanFMA_CONTROLROOM:	cleanFMA_CONTROLROOM_LVL

FMA_CONTROLROOM_IN  :=	$(LEVELS_IN_DIR)/FMA/CONTROLROOM/CONTROLROOM.mex
FMA_CONTROLROOM_OUT :=	$(LEVELS_OUT_DIR)/FMA_CONTROLROOM.lvl
FMA_CONTROLROOM_TEX :=	$(LEVELS_OUT_DIR)/FMA_CONTROLROOM.tex

cleanFMA_CONTROLROOM_LVL :
	$(RM) -f $(FMA_CONTROLROOM_OUT) $(FMA_CONTROLROOM_TEX)
FMA_CONTROLROOM_LVL :	$(FMA_CONTROLROOM_IN)

$(FMA_CONTROLROOM_OUT) : $(FMA_CONTROLROOM_IN)
	@$(MKLEVEL) $(FMA_CONTROLROOM_IN) -o:$(FMA_CONTROLROOM_OUT) -i:$(INC_DIR) $(LEVELS_OPTS) $(FMA_CONTROLROOM_OPTS)

