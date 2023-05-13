MermaidMan_FMA_ITEMOFS:	$(MermaidMan_FMA_ITEMOFS_OUT)

MermaidMan_FMA_ITEMOFS_IN :=	$(ACTOR_IN_DIR)/MermaidMan_FMA_ITEMOFS/$(ACTOR_SPRITE_DIR)/*
MermaidMan_FMA_ITEMOFS_OUT :=	$(ACTOR_OUT_DIR)/MermaidMan_FMA_ITEMOFS.sbk

$(MermaidMan_FMA_ITEMOFS_OUT) : $(MermaidMan_FMA_ITEMOFS_IN)
	@$(MKACTOR) -r:$(ACTOR_IN_DIR) -s:$(ACTOR_SPRITE_DIR) -o:$(ACTOR_OUT_DIR) -i:$(INC_DIR) MermaidMan_FMA_ITEMOFS $(MKACTOR_OPTS)

