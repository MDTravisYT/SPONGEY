LettersAndNames=
(
	"A","ANGRY",
	"B","BORED",
	"C","CHEER",
	"F","FIGHT",
	"H","THROW",
	"I","ITCH",
	"K","CRY",
	"L","LOOPLEASE",
	"N","SLIDE",
	"O","DEAD",
	"R","RUN",
	"S","STAND",
	"T","TUMBLE",
#	"U","WATING",
	"V","VOMIT",
	"W","WALK",
	"Y","YARN",
);

foreach $Val (keys %LettersAndNames)
	{
	push (@Letters,$Val);
	}

while (<>)
	{
	foreach $Letter (@Letters)
		{
		if (/(FRM_CH\d$Letter\d+)/)
			{
			$AllFrames{$Letter}.=":$1";
			}
		}
	}
print ("/* Generated by anim.pl, so please don't go hand editing this file like some sort of cunt. xxxx gaz. */ \n");

print ("#include \"data\\graf\\kid.h\"\n");
print ("#include \"gfx\\anim.h\"\n\n");

foreach $Letter (@Letters)
	{
	@ThisLettersFrames=split(/:/,$AllFrames{$Letter});

	$LargestFrame=0;

	foreach $Frame (@ThisLettersFrames)
		{
		$Frame=~/FRM_CH\d$Letter(\d+)/;
		$LargestFrame=$1 if ($1 > $LargestFrame);
		}

		{

		$LargestFrame=sprintf("%d",$LargestFrame);
		$NumOfFrames=$LargestFrame+1;

		for ($f=1;$f<6;$f++)
			{
			printf("static u16 const ANM_$LettersAndNames{$Letter}$f\[$NumOfFrames\]={",);

			for ($i=0;$i<$NumOfFrames;$i++)
			  {
			  $Str=sprintf("FRM_CH$f$Letter%04d,",$i);
			  print $Str;
			  }

			print "};\n";
			}
		print("\nstatic ANM const ANM_$LettersAndNames{$Letter}={");
		print ("$NumOfFrames,");
		print ("{");

		for ($f=1;$f<6;$f++)
			{
			print "ANM_$LettersAndNames{$Letter}$f,";
			}
		print ("}};\n\n\n");
		}
	}

print "ANM const * const AnimTab[]=\n{\n";

foreach $Letter (@Letters)
	{
	print "\t&ANM_$LettersAndNames{$Letter},\n";

	}

print "};\n";



