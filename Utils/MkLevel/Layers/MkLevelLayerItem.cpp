/******************/
/*** Layer Item ***/
/******************/

#include	<Davelib.h>
#include	<List2d.h>

//#include	"MkLevel.h"
#include	"MkLevelLayerItem.h"


/*****************************************************************************/
/*****************************************************************************/
/*** Pre-Process *************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void	CMkLevelLayerItem::PreProcess(CMkLevel *Core)
{
}

/*****************************************************************************/
/*****************************************************************************/
/*** Process *****************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void	CMkLevelLayerItem::Process(CMkLevel *Core)
{
		ProcessList(Core);
}

/*****************************************************************************/
/*****************************************************************************/
/** Write ********************************************************************/
/*****************************************************************************/
/*****************************************************************************/
int		CMkLevelLayerItem::Write(CMkLevel *Core,FILE *File,const char *LayerName)
{
int			ThisPos=ftell(File);
sThingHdr	Hdr;
int			i,ListSize=ThingList.size();
		
		Hdr.Count=ListSize;
		fwrite(&Hdr,sizeof(sThingHdr),1,File);

		for (i=0; i<ListSize; i++)
		{
			sMkLevelLayerThing	&ThisThing=ThingList[i];
			sThingItem			OutThing;

			OutThing.Type=ThisThing.Type;
			OutThing.Pos.X=ThisThing.XY[0].x;
			OutThing.Pos.Y=ThisThing.XY[0].y;
			fwrite(&OutThing,sizeof(sThingItem),1,File);
		}

		Size=ftell(File)-ThisPos;
		return(ThisPos);
}

/*****************************************************************************/
