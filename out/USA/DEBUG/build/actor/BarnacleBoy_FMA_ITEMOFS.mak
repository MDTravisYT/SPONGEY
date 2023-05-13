BarnacleBoy_FMA_ITEMOFS:	$(BarnacleBoy_FMA_ITEMOFS_OUT)

BarnacleBoy_FMA_ITEMOFS_IN :=	$(ACTOR_IN_DIR)/BarnacleBoy_FMA_ITEMOFS/$(ACTOR_SPRITE_DIR)/*
BarnacleBoy_FMA_ITEMOFS_OUT :=	$(ACTOR_OUT_DIR)/BarnacleBoy_FMA_ITEMOFS.sbk

$(BarnacleBoy_FMA_ITEMOFS_OUT) : $(BarnacleBoy_FMA_ITEMOFS_IN)
	@$(MKACTOR) -r:$(ACTOR_IN_DIR) -s:$(ACTOR_SPRITE_DIR) -o:$(ACTOR_OUT_DIR) -i:$(INC_DIR) BarnacleBoy_FMA_ITEMOFS $(MKACTOR_OPTS)


