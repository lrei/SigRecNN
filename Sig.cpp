#include "Sig.h"

using namespace std;
Sig::Sig()
{
	normalized = false;
	projected = false;
}
Sig::Sig(string path)
{
	load(path);
}

/* Default Input Depth */
int Sig::getInDepth()
{
	return 8;
}
/* Default Input Width */
int Sig::getInWidth()
{
	return 512;
}
/* Default Input Height */
int Sig::getInHeight()
{
	return 128;
}
/* Default Normalization factor
 * width and height get divided by this value to create the normalized image
 */
int Sig::getFactor()
{
	return 4;
}

/* load signature from a BMP file */
bool Sig::load(string path)
{	
	/* reset flags */
	normalized = false;
	projected = false;
	
	/* Read signature from file */
	if (!bsig.ReadFromFile(path.c_str())) {
		cout << "Error: Unable to read file" << endl;
		exit(0);
	}
	/*
	 * Check if the signature is in the expected format
	 */

	/* Check Depth */
	if (bsig.TellBitDepth() != getInDepth()) {
		cerr << "Error in " << path << ": BMP depth must be "
			 << getInDepth() << "." << endl;
		exit(1);
	}
	/* Check Width */
	if (bsig.TellWidth() != getInWidth()) {
		cerr << "Error in " << path << ": BMP width must be "
			 << getInWidth() << "." << endl;
		exit(1);
	}
	/* Check Height */
	if (bsig.TellHeight() != getInHeight()) {
		cerr << "Error in " << path << ": BMP height must be "
			 << getInHeight() << "." << endl;
		exit(1);
	}
	
	return true;
}

/* check if signature is already normalized */
bool Sig::isnormalized()
{
	return normalized;
}
/*
 * Normalize the signature
 * Aligns it to the upper left corner and streches it without changing
 * the aspect ratio.
 */
bool Sig::normalize()
{
	BMP tempsig, auxsig;
	RGBApixel pixel;
	int nw, nh, startx, starty, endx, endy, tw, th;
	bool flag = false;
	
	if (normalized)
		return true; 	// image is already normalized
		
	nw = bsig.TellWidth();
	nh = bsig.TellHeight();


	/* 
	 * Align Signature to the Left
	 */
 
	/* search for the first non-empty collumn (left to right) */
	for (int xx = 0; xx < nw; xx++) {
		for (int yy = 0; yy < nh; yy++) {
			pixel = bsig.GetPixel(xx, yy);
			if (pixelIsBlack(pixel)) {
				startx = xx;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	
	/* copy to a temporary BMP with new starting x */
	tempsig.SetBitDepth(8);
	tempsig.SetSize(nw, nh);
	RangedPixelToPixelCopy(bsig, startx, nw-1, 0, nh-1, tempsig, 0, 0);
	
	flag = false; 	// reset flag
	
	/* 
	 * Align Signature up
	 */
	
	/* search for the first non-empty line (top to bottom) */
	for (int yy = 0; yy < nh; yy++) {
		for (int xx = 0; xx < nw; xx++) {
			pixel = bsig.GetPixel(xx, yy);
			if (pixelIsBlack(pixel)) {
				starty = yy;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	
	/* copy back with new values (both x and y) */
	bsig.SetSize(nw, nh);	// blank original first - using SetSize to do it
	RangedPixelToPixelCopy(tempsig, 0, nw-1, starty, nh-1, bsig, 0, 0);

	// signature now starts at the top left corner

	/*
	 * Scale the image
	 */
	 /* search for the last non-empty line (top to bottom) */
	for (int yy = 0; yy < nh; yy++) {
		for (int xx = 0; xx < nw; xx++) {
			pixel = bsig.GetPixel(xx, yy);
			if (pixelIsBlack(pixel)) {
				endy = yy;
			}
		}
	}
	 /* search for the last non-empty column (left to right) */
	for (int xx = 0; xx < nw; xx++) {
		for (int yy = 0; yy < nh; yy++) {
			pixel = bsig.GetPixel(xx, yy);
			if (pixelIsBlack(pixel)) {
				endx = xx;
			}
		}
	}
	/* copy to a temporary and auxilary BMP with new sizes */
	tempsig.SetSize(endx+1, endy+1);
	RangedPixelToPixelCopy(bsig, 0, endx+1, 0, endy+1, tempsig, 0, 0);

	auxsig.SetBitDepth(8);
	auxsig.SetSize(endx+1, endy+1);
	RangedPixelToPixelCopy(bsig, 0, endx+1, 0, endy+1, auxsig, 0, 0);
	
	// tempsig contains the minimum ammount of white pixels
	// i.e. the signature occuppies the entire space of the image
	// current image size is end+1 * endy+1
	
	/* use auxsig to determine scaling factor */
	tw = getInWidth() / getFactor();
	th = getInHeight() / getFactor();
	
	if ((nw - auxsig.TellWidth()) < (nh - auxsig.TellHeight())) {
		do {
			Rescale(auxsig, 'W', tw);
			tw--;
		} while (auxsig.TellHeight() > th);
		Rescale(tempsig, 'W', tw);
	}
	else {
		do {
			Rescale(auxsig, 'H', th);
			th--;
		} while (auxsig.TellWidth() > tw);
		Rescale(tempsig, 'H', th);
	}
	
	nw = getInWidth() / getFactor();
	nh = getInHeight() / getFactor();
	
	// copy back the image	
	bsig.SetSize(nw, nh);	// blank original first - using SetSize to do it
	RangedPixelToPixelCopy(tempsig, 0, nw-1, 0, nh-1, bsig, 0, 0);

	


	normalized = true;	// set the normalized flag
	
	return true;
}
/*
 * Save the signature in normalized form
 * Normalize it if necessary.
 * The resulting file will be in path + .bmp so if path = "nn/x" the file will
 * be saved as nn/x.bmp
 */
bool Sig::saveNormalized(string path)
{
	string fPath = path + ".bmp";
	normalize();
	
	bsig.WriteToFile(fPath.c_str());
	return true;
}

/* check if signature projections have been extracted */
bool Sig::isprojected()
{
	return projected;
}

/* 
 * Extracts Projections at 0º, 90º, 1280º and 270º 
 * normalize if necessary 
 */
bool Sig::projections()
{
	RGBApixel pixel, BLACK;
	int nw, nh, xx, yy;
	
	
	if(projected)
		return true;
	
	normalize();
	
	BLACK.Alpha = BLACK.Red = BLACK.Blue = BLACK.Green = 0;
	
	nw = bsig.TellWidth();
	nh = bsig.TellHeight();
	
	/*
	 * Extract projection at 0º
	 */
	proj[0].SetBitDepth(8);
	proj[0].SetSize(nw, nh);
	
	/* get the first Y for every X */
	for (xx = 0; xx < nw; xx++) {
		for (yy = 0; yy < nh; yy++) {
			pixel = bsig.GetPixel(xx, yy);
			if (!pixelIsWhite(pixel)) {
				proj[0].SetPixel(xx, yy, BLACK);
				break;	// go to next xx
			}
		}
	}
	/*
	 * Extract projection at 90º
	 */
	proj[1].SetBitDepth(8);
	proj[1].SetSize(nw, nh);
	
	/* get the first X for every Y */
	for (yy = 0; yy < nh; yy++) {
		for (xx = 0; xx < nw; xx++) {
			pixel = bsig.GetPixel(xx, yy);
			if (!pixelIsWhite(pixel)) {
				proj[1].SetPixel(xx, yy, BLACK);
				break;	// go to next yy
			}
		}
	}
	/*
	 * Extract projection at 180º
	 */
	proj[2].SetBitDepth(8);
	proj[2].SetSize(nw, nh);
	
	/* get the last Y for every X */
	for (xx = 0; xx < nw; xx++) {
		for (yy = nh-1; yy >= 0; yy--) {
			pixel = bsig.GetPixel(xx, yy);
			if (!pixelIsWhite(pixel)) {
				proj[2].SetPixel(xx, yy, BLACK);
				break;	// go to next xx
			}
		}
	}
	/*
	 * Extract projection at 270º
	 */
	proj[3].SetBitDepth(8);
	proj[3].SetSize(nw, nh);
	
	/* get the last X for every Y */
	for (yy = 0; yy < nh; yy++) {
		for (xx = nw-1; xx >= 0; xx--) {
			pixel = bsig.GetPixel(xx, yy);
			if (!pixelIsWhite(pixel)) {
				proj[3].SetPixel(xx, yy, BLACK);
				break;	// go to next yy
			}
		}
	}

	return true;
}

/* 
 * Save signature projections 
 * Create them if necessary.
 */
bool Sig::saveProjections(string path)
{
	string fPath;
	ostringstream s;
	projections();
	
	
	for (int ii = 0; ii < 4; ii++) {
		fPath = path + ".p";
		s.str("");
		s << ii;
		fPath += s.str();
		fPath += ".bmp";
		proj[ii].WriteToFile(fPath.c_str());
	}
	return true;
}

/* 
 * Convert the signature and it's projections to an array.
 * Normalizes and projects if necessary 
 * Divides images into blocks 32x4
 */
double *Sig::toArray()
{
	RGBApixel pixel;
	int ii, nw, nh;
	double *array;
	int dx, dy, arrSize, pixden;

	normalize();
	projections();

	nw = bsig.TellWidth();
	nh = bsig.TellHeight();
	// TODO: this needs to NOT be hardcoded
	arrSize = 8*2;	// blocks for the signature and for the projections
	arrSize *= 2;	// currently using 2 projections
	arrSize += 1;	// for the terminating value
	TERM = (double) -1.0;	// set value of the terminator
	array = new double [arrSize];
	ii = 0; dx = 16; dy = 16; // dx and dy divide X and Y respectively into blocks
	
	/* Initialize array */
	for (int jj = 0; jj < arrSize; jj++)
		array[jj] = (double) 0.0;
	
	/* for the signature *
	pixden = 0;	// pixel density in a block
	for (int yy = 0; yy < nh-dy+1; yy+=dy) {
		for (int xx = 0; xx < nw-dx+1; xx+=dx) {
			for (int ny = 0; ny < dy; ny++) {
				for (int nx = 0; nx < dx; nx++) {
					pixel = bsig.GetPixel(xx+nx, yy+ny);
					if (pixelIsBlack(pixel))
						pixden++;
				} // nx
			} // ny
			array[ii] = (double) pixden;
			pixden = 0;
			ii++;		
		} // xx
	} // yy
	
	
	/* for the projections */
	pixden = 0;
	for (int pp = 0; pp < 2; pp++) {	// currently takes only projs 0º and 90º 
		for (int yy = 0; yy < nh-dy+1; yy+=dy) {
			for (int xx = 0; xx < nw-dx+1; xx+=dx) {
				for (int ny = 0; ny < dy; ny++) {
					for (int nx = 0; nx < dx; nx++) {
						pixel = proj[pp].GetPixel(xx+nx, yy+ny);
						if (pixelIsBlack(pixel))
							pixden++;
					} // nx
				} // ny
			array[ii] = (double) pixden;
			pixden = 0;
			ii++;	
			} // xx
		} // yy
	} // pp
	
	array[ii] = TERM;
	
	return array;
}

/* 
 * Save signature projections 
 * Create them if necessary.
 * TODO: NOT DONE .
 */
bool Sig::saveArray(string filepath)
{
	int ii;
	double *array;
	ofstream file(filepath.c_str());
	
	array = toArray();
	
	/* Write */
	for (ii = 0; array[ii] != TERM; ii++)
		file << array[ii] << " ";	// " " will have to be ignored
	file << endl;	// endl will also have to be ignored i.e. ignore.in(1)
	
	file.close();
	return true;
}

Sig::~Sig()
{
}
