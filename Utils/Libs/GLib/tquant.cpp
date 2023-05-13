/**********************************************************************
	    C Implementation of Wu's Color Quantizer (v. 2)
	    (see Graphics Gems vol. II, pp. 126-133)

Author:	Wu
	Dept. of Computer Science
	Univ. of Western Ontario
	London, Ontario N6A 5B7
	wu@csd.uwo.ca

Algorithm: Greedy orthogonal bipartition of RGB space for variance
	   minimization aided by inclusion-exclusion tricks.
	   For speed no nearest neighbor search is done. Slightly
	   better performance can be expected by more sophisticated
	   but more expensive versions.

The author thanks Tom Lane at Tom_Lane@G.GP.CS.CMU.EDU for much of
additional documentation and a cure to a previous bug.

Free to distribute, comments and suggestions are appreciated.
**********************************************************************/	

#include "Tquant.h"
#include "gobject.hpp"


#define MAXCOLOR	256
#define	RED	2
#define	GREEN	1
#define BLUE	0

struct box {
    int r0;			 /* min value, exclusive */
    int r1;			 /* max value, inclusive */
    int g0;  
    int g1;  
    int b0;  
    int b1;
    int vol;
};

/* Histogram is in elements 1..HISTSIZE along each axis,
 * element 0 is for base or marginal value
 * NB: these must start out 0!
 */

float gm2[33][33][33];
long int wt[33][33][33], mr[33][33][33],	mg[33][33][33],	mb[33][33][33];
unsigned char *Ir, *Ig, *Ib;
//int size;						/*image size*/
//int K;							/*color look-up table size*/
unsigned short int *Qadd;
void ClearTables(void);


void ClearTables(void)
{
	for (int x=0;x<33;x++)
		for (int y=0;y<33;y++)
			for (int z=0;z<33;z++)
				{
				gm2[x][y][z]=0;
				wt[x][y][z]=0;
				mr[x][y][z]=0;
				mg[x][y][z]=0;
				mb[x][y][z]=0;
				}
}



/* build 3-D color histogram of counts, r/g/b, c^2 */
void Hist3d(long int* vwt, long int *vmr, long int *vmg, long int *vmb, float *m2, int size)
{
	register int ind, r, g, b;
	int	     inr, ing, inb, table[256];
	register long int i;
		
	for(i=0; i<256; ++i) table[i]=i*i;
	Qadd = (unsigned short int *)malloc(sizeof(short int)*size);
	if (Qadd==NULL)
		GObject::Error(ERM_OUTOFMEM);

	for(i=0; i<size; ++i)
	{
		r = Ir[i]; g = Ig[i]; b = Ib[i];
		inr=(r>>3)+1; 
		ing=(g>>3)+1; 
		inb=(b>>3)+1; 
		Qadd[i]=ind=(inr<<10)+(inr<<6)+inr+(ing<<5)+ing+inb;
		/*[inr][ing][inb]*/
		++vwt[ind];
		vmr[ind] += r;
		vmg[ind] += g;
		vmb[ind] += b;
		m2[ind] += (float)(table[r]+table[g]+table[b]);
	}
}

/* At conclusion of the histogram step, we can interpret
 *   wt[r][g][b] = sum over voxel of P(c)
 *   mr[r][g][b] = sum over voxel of r*P(c)  ,  similarly for mg, mb
 *   m2[r][g][b] = sum over voxel of c^2*P(c)
 * Actually each of these should be divided by 'size' to give the usual
 * interpretation of P() as ranging from 0 to 1, but we needn't do that here.
 */

/* We now convert histogram into moments so that we can rapidly calculate
 * the sums of the above quantities over any desired box.
 */

 /* compute cumulative moments. */
void M3d(long int *vwt, long int *vmr, long int *vmg, long int *vmb, float *m2)
{
	register unsigned short int ind1, ind2;
	register unsigned char i, r, g, b;
	long int line, line_r, line_g, line_b;
	long int area[33], area_r[33], area_g[33], area_b[33];
	float line2, area2[33];

    for(r=1; r<=32; ++r)
	{
		for(i=0; i<=32; ++i)
		{
		    area[i]=area_r[i]=area_g[i]=area_b[i]=0;
			area2[i]=0.f;
		}
		for(g=1; g<=32; ++g)
		{
		    line = line_r = line_g = line_b = 0;
			line2 = 0.f;
		    for(b=1; b<=32; ++b)
			{
				ind1 = (r<<10) + (r<<6) + r + (g<<5) + g + b; /* [r][g][b] */
				line += vwt[ind1];
				line_r += vmr[ind1]; 
				line_g += vmg[ind1]; 
				line_b += vmb[ind1];
				line2 += m2[ind1];
				area[b] += line;
				area_r[b] += line_r;
				area_g[b] += line_g;
				area_b[b] += line_b;
				area2[b] += line2;
				ind2 = ind1 - 1089; /* [r-1][g][b] */
				vwt[ind1] = vwt[ind2] + area[b];
				vmr[ind1] = vmr[ind2] + area_r[b];
				vmg[ind1] = vmg[ind2] + area_g[b];
				vmb[ind1] = vmb[ind2] + area_b[b];
				m2[ind1] = m2[ind2] + area2[b];
		    }
		}
    }
}


/* Compute sum over a box of any given statistic */
long int Vol(box *cube, long int *mmt)
{
    return( mmt[((cube->r1)*33*33)+((cube->g1)*33)+(cube->b1)]
	   -mmt[((cube->r1)*33*33)+((cube->g1)*33)+(cube->b0)]
	   -mmt[((cube->r1)*33*33)+((cube->g0)*33)+(cube->b1)]
	   +mmt[((cube->r1)*33*33)+((cube->g0)*33)+(cube->b0)]
	   -mmt[((cube->r0)*33*33)+((cube->g1)*33)+(cube->b1)]
	   +mmt[((cube->r0)*33*33)+((cube->g1)*33)+(cube->b0)]
	   +mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b1)]
	   -mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b0)] );
}

/* The next two routines allow a slightly more efficient calculation
 * of Vol() for a proposed subbox of a given box.  The sum of Top()
 * and Bottom() is the Vol() of a subbox split in the given direction
 * and with the specified new upper bound.
 */

/* Compute part of Vol(cube, mmt) that doesn't depend on r1, g1, or b1 */
/* (depending on dir) */
long int Bottom(box *cube, unsigned char dir, long int *mmt)
{
    switch(dir){
	case RED:
	    return( -mmt[((cube->r0)*33*33)+((cube->g1)*33)+(cube->b1)]
		    +mmt[((cube->r0)*33*33)+((cube->g1)*33)+(cube->b0)]
		    +mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b1)]
		    -mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b0)] );
	    break;
	case GREEN:
	    return( -mmt[((cube->r1)*33*33)+((cube->g0)*33)+(cube->b1)]
		    +mmt[((cube->r1)*33*33)+((cube->g0)*33)+(cube->b0)]
		    +mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b1)]
		    -mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b0)] );
	    break;
	case BLUE:
	    return( -mmt[((cube->r1)*33*33)+((cube->g1)*33)+(cube->b0)]
		    +mmt[((cube->r1)*33*33)+((cube->g0)*33)+(cube->b0)]
		    +mmt[((cube->r0)*33*33)+((cube->g1)*33)+(cube->b0)]
		    -mmt[((cube->r0)*33*33)+((cube->g0)*33)+(cube->b0)] );
	    break;
	default:
		return NULL;
    }
}


/* Compute remainder of Vol(cube, mmt), substituting pos for */
/* r1, g1, or b1 (depending on dir) */
long int Top(box *cube, unsigned char dir, int pos, long int *mmt)
{
    switch(dir){
	case RED:
	    return( mmt[(pos*33*33)+(cube->g1*33)+cube->b1] 
		   -mmt[(pos*33*33)+(cube->g1*33)+cube->b0]
		   -mmt[(pos*33*33)+(cube->g0*33)+cube->b1]
		   +mmt[(pos*33*33)+(cube->g0*33)+cube->b0] );
	    break;
	case GREEN:
	    return( mmt[((cube->r1)*33*33)+(pos*33)+cube->b1] 
		   -mmt[((cube->r1)*33*33)+(pos*33)+cube->b0]
		   -mmt[((cube->r0)*33*33)+(pos*33)+cube->b1]
		   +mmt[((cube->r0)*33*33)+(pos*33)+cube->b0] );
	    break;
	case BLUE:
	    return( mmt[(cube->r1*33*33)+(cube->g1*33)+pos]
		   -mmt[(cube->r1*33*33)+(cube->g0*33)+pos]
		   -mmt[(cube->r0*33*33)+(cube->g1*33)+pos]
		   +mmt[(cube->r0*33*33)+(cube->g0*33)+pos] );
	    break;
	default:
		return NULL;
    }
}


/* Compute the weighted variance of a box */
/* NB: as with the raw statistics, this is really the variance * size */
float Var(box *cube)
{
	float dr, dg, db, xx;

    dr = (float)Vol(cube, &mr[0][0][0]);
    dg = (float)Vol(cube, &mg[0][0][0]);
    db = (float)Vol(cube, &mb[0][0][0]);
    xx =  gm2[cube->r1][cube->g1][cube->b1] 
	 -gm2[cube->r1][cube->g1][cube->b0]
	 -gm2[cube->r1][cube->g0][cube->b1]
	 +gm2[cube->r1][cube->g0][cube->b0]
	 -gm2[cube->r0][cube->g1][cube->b1]
	 +gm2[cube->r0][cube->g1][cube->b0]
	 +gm2[cube->r0][cube->g0][cube->b1]
	 -gm2[cube->r0][cube->g0][cube->b0];

    return( xx - (dr*dr+dg*dg+db*db)/(float)Vol(cube,&wt[0][0][0]) );
}

/* We want to minimize the sum of the variances of two subboxes.
 * The sum(c^2) terms can be ignored since their sum over both subboxes
 * is the same (the sum for the whole box) no matter where we split.
 * The remaining terms have a minus sign in the variance formula,
 * so we drop the minus sign and MAXIMIZE the sum of the two terms.
 */

float Maximize(box *cube, unsigned char dir, int first, int last, int *cut,long int whole_r, long int whole_g, long int whole_b, long int whole_w)
{
	register long int half_r, half_g, half_b, half_w;
	long int base_r, base_g, base_b, base_w;
	register int i;
	register float temp, max;

    base_r = Bottom(cube, dir, &mr[0][0][0]);
    base_g = Bottom(cube, dir, &mg[0][0][0]);
    base_b = Bottom(cube, dir, &mb[0][0][0]);
    base_w = Bottom(cube, dir, &wt[0][0][0]);
    max = 0.0;
    *cut = -1;
    for(i=first; i<last; ++i)
	{
		half_r = base_r + Top(cube, dir, i, &mr[0][0][0]);
		half_g = base_g + Top(cube, dir, i, &mg[0][0][0]);
		half_b = base_b + Top(cube, dir, i, &mb[0][0][0]);
		half_w = base_w + Top(cube, dir, i, &wt[0][0][0]);
		/* now half_x is sum over lower half of box, if split at i */
        if (half_w == 0) {      /* subbox could be empty of pixels! */
          continue;             /* never split into an empty box */
		} else
		temp = ((float)half_r*half_r + (float)half_g*half_g +
				(float)half_b*half_b)/half_w;

		half_r = whole_r - half_r;
		half_g = whole_g - half_g;
		half_b = whole_b - half_b;
		half_w = whole_w - half_w;
		if (half_w == 0) {      /* subbox could be empty of pixels! */
			continue;           /* never split into an empty box */
		} else
        temp += ((float)half_r*half_r + (float)half_g*half_g +
                 (float)half_b*half_b)/half_w;

    	if (temp > max) {max=temp; *cut=i;}
    }
    return(max);
}

int Cut(box *set1, box *set2)
{
	unsigned char dir;
	int cutr, cutg, cutb;
	float maxr, maxg, maxb;
	long int whole_r, whole_g, whole_b, whole_w;

    whole_r = Vol(set1, &mr[0][0][0]);
    whole_g = Vol(set1, &mg[0][0][0]);
    whole_b = Vol(set1, &mb[0][0][0]);
    whole_w = Vol(set1, &wt[0][0][0]);

    maxr = Maximize(set1, RED, set1->r0+1, set1->r1, &cutr,
		    whole_r, whole_g, whole_b, whole_w);
    maxg = Maximize(set1, GREEN, set1->g0+1, set1->g1, &cutg,
		    whole_r, whole_g, whole_b, whole_w);
    maxb = Maximize(set1, BLUE, set1->b0+1, set1->b1, &cutb,
		    whole_r, whole_g, whole_b, whole_w);

    if( (maxr>=maxg)&&(maxr>=maxb) )
	{
		dir = RED;
		if (cutr < 0) return 0; /* can't split the box */
    }else
    if( (maxg>=maxr)&&(maxg>=maxb) ) 
	dir = GREEN;
    else
	dir = BLUE; 

    set2->r1 = set1->r1;
    set2->g1 = set1->g1;
    set2->b1 = set1->b1;

    switch (dir){
	case RED:
	    set2->r0 = set1->r1 = cutr;
	    set2->g0 = set1->g0;
	    set2->b0 = set1->b0;
	    break;
	case GREEN:
	    set2->g0 = set1->g1 = cutg;
	    set2->r0 = set1->r0;
	    set2->b0 = set1->b0;
	    break;
	case BLUE:
	    set2->b0 = set1->b1 = cutb;
	    set2->r0 = set1->r0;
	    set2->g0 = set1->g0;
	    break;
    }
    set1->vol=(set1->r1-set1->r0)*(set1->g1-set1->g0)*(set1->b1-set1->b0);
    set2->vol=(set2->r1-set2->r0)*(set2->g1-set2->g0)*(set2->b1-set2->b0);
    return 1;
}


void Mark(box *cube, int label, unsigned char *tag)
{
	register int r, g, b;

	for(r=cube->r0+1; r<=cube->r1; ++r)
		for(g=cube->g0+1; g<=cube->g1; ++g)
			for(b=cube->b0+1; b<=cube->b1; ++b)
				tag[(r<<10) + (r<<6) + r + (g<<5) + g + b] = label;
}



void tquant(BYTE* Src, BYTE* Dst, BYTE* Pal, int K, int size)
{
	struct box	cube[MAXCOLOR];
	unsigned char	*tag;
	unsigned char	lut_r[MAXCOLOR], lut_g[MAXCOLOR], lut_b[MAXCOLOR];
	int	next;
	register long int	i, weight;
	register int	k;
	float	vv[MAXCOLOR], temp;

	ClearTables();

	/* input R,G,B components into Ir, Ig, Ib;
	   set size to width*height */

//	screen_debug_msg("Reducing to %d cols",K);


	Ir=(BYTE*)malloc(size);
	Ig=(BYTE*)malloc(size);
	Ib=(BYTE*)malloc(size);

	/* Split in data into RGB buffers */
	for(i=0;i<size;i++)
	{
		Ir[i]=*Src++;
		Ig[i]=*Src++;
		Ib[i]=*Src++;
	}

	Hist3d(&wt[0][0][0], &mr[0][0][0], &mg[0][0][0], &mb[0][0][0], &gm2[0][0][0], size);
	free(Ig); free(Ib); free(Ir);

	M3d(&wt[0][0][0], &mr[0][0][0], &mg[0][0][0], &mb[0][0][0], &gm2[0][0][0]);

	cube[0].r0 = cube[0].g0 = cube[0].b0 = 0;
	cube[0].r1 = cube[0].g1 = cube[0].b1 = 32;
	next = 0;

		for(i=1; i<K; ++i)
		{
            if (Cut(&cube[next], &cube[i])) {
              /* volume test ensures we won't try to cut one-cell box */
              vv[next] = (cube[next].vol>1) ? Var(&cube[next]) : 0.f;
              vv[i] = (cube[i].vol>1) ? Var(&cube[i]) : 0.f;
	    } else {
              vv[next] = 0.0;   /* don't try to split this box again */
              i--;              /* didn't create box i */
	    }
            next = 0; temp = vv[0];
            for(k=1; k<=i; ++k)
                if (vv[k] > temp) {
                    temp = vv[k]; next = k;
		}
            if (temp <= 0.0) {
              K = i+1;
              break;
	    }
	}

	/* the space for array gm2 can be freed now */

	tag = (unsigned char *)malloc(33*33*33);
	if (tag==NULL)
		GObject::Error(ERM_OUTOFMEM);

	for(k=0; k<K; ++k){
	    Mark(&cube[k], k, tag);
	    weight = Vol(&cube[k], &wt[0][0][0]);
	    if (weight) {
		lut_r[k] = (unsigned char)(Vol(&cube[k], &mr[0][0][0]) / weight);
		lut_g[k] = (unsigned char)(Vol(&cube[k], &mg[0][0][0]) / weight);
		lut_b[k] = (unsigned char)(Vol(&cube[k], &mb[0][0][0]) / weight);
	    }
	    else{
	      lut_r[k] = lut_g[k] = lut_b[k] = 0;		
	    }
	}

	for(i=0; i<size; ++i) Qadd[i] = tag[Qadd[i]];

	/* output lut_r, lut_g, lut_b as color look-up table contents,
	   Qadd as the quantized image (array of table addresses). */

	for(i=0; i<size; ++i) *Dst++ = (unsigned char)Qadd[i];
	free(Qadd);

	for(i=0;i<K;i++)
	{
		*Pal++=lut_r[i];
		*Pal++=lut_g[i];
		*Pal++=lut_b[i];
	}
	
	free(tag);
}

