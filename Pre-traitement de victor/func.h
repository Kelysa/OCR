#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

int filtre_gris(int r, int g, int b)
{
    return (r+g+b)/3;
}
int white_black(int moyen)
{
    if (moyen > 128){
            moyen = 255;
        }
        else{ moyen = 0;}
    return moyen;
}

int[] Color_Invert(int r, int v, int b)
		{
		    int[] color;
			color[0] = 255 - r;
			color[1] = 255 - v;
			color[2] = 255 - b;
			return color;
		}
int Color_Grayscale(int r, int v, int b)
		{
            r = (0.21F * r);
			v = (0.72F * v);
			b = (0.07F * b);
			int result = r + g + b;
			return result;
		}
int[] Color_Contrast(int r, int v, int b, int delta)
		{
			if (delta > 255)
			{
				delta = 255;
			}
			if (delta < -255)
			{
				delta = -255;
			}
			double F = (259 * (delta + 255)) / (255 * (259 - delta));
			r = F * (color.R - 128) + 128;
			v = (F * (color.G - 128) + 1280);
			b = (F * (color.B - 128) + 128);
			return [r,v,b];
		}

#endif // FUNC_H_INCLUDED
