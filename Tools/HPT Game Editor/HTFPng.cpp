// HTFPng.cpp: implementation of the HTFPng class.
//
//////////////////////////////////////////////////////////////////////

#include "HTFPng.h"
#include<algorithm>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



HTFPng::HTFPng():
data_length(0)
{

}

HTFPng::~HTFPng()

{

	//delete png chunks
 /*	for(int i=0; i<png_chunks.size(); i++)
	{
		delete png_chunks[i];
	}

	delete matrix_data;
  */
}

void HTFPng::write_file(FILE *fp)
{
	int file_type =2;
	
	num_tiles = flat_tiles.size();
	total_width = num_tiles*16;

	color_key_red = 255;
	color_key_green = 0;
	color_key_blue = 255;
	fwrite(HTF, sizeof(char),3,fp);
	fwrite(&version, sizeof(int), 1,fp);
	fwrite(&output_image_width, sizeof(int), 1,fp);
	fwrite(&output_image_height, sizeof(int), 1,fp);
/*	fwrite(&total_width, sizeof(int), 1,fp);
	fwrite(&color_key_red, sizeof(int), 1,fp);
	fwrite(&color_key_green, sizeof(int), 1,fp);
	fwrite(&color_key_blue, sizeof(int), 1,fp);
*/
        int rows,last_column,columns;
        rows = (flat_tiles.size() / 64);
        last_column = flat_tiles.size() % 64;
        if(rows == 0) columns = last_column;
        else columns = 64;
        if(last_column != 0) rows++;
        else last_column = 64;

	fwrite(&rows, sizeof(int), 1,fp);
        for(int count = 0;count < (rows-1);count++)
        {
             fwrite(&columns, sizeof(int), 1,fp);
        }
        fwrite(&last_column, sizeof(int), 1,fp);

	//write out image data
/*	fwrite(&data_length, sizeof(int), 1,fp);

	for(int i=1; i< png_chunks.size()-1; i++)
		fwrite(png_chunks[i]->data, png_chunks[i]->Length, 1,fp);
*/
	fwrite(&compressed_output_image_size, sizeof(int), 1,fp);
	
	fwrite(compressed_output_image, sizeof(char), compressed_output_image_size,fp);

	fwrite(&matrix_width, sizeof(int), 1,fp);
	fwrite(&matrix_height, sizeof(int), 1,fp);

//	fwrite(matrix_data, sizeof(unsigned char), matrix_width*matrix_height*9,fp);
	fwrite(tiles, sizeof(Tile), matrix_width*matrix_height,fp);
}

void HTFPng::load_image_data(FILE *&fp)
{

        fscanf(fp,"%i",&num_tiles);

        unsigned char buffer[16*16*3];
        FlatTile tempt;
        int keycounter = 0;
        tempt.ClearTile();
        tempt.key = 0;
        flat_tiles.push_back(tempt);
        int count,y,x,temp;
        for(count = 0;count < num_tiles;count++)
        {
                for(y=0;y<16;y++)
                {
                        for(x=0;x<16;x++)
                        {
                                fscanf(fp,"%i",&temp);
                                buffer[16*y*3+x*3] = (unsigned char)temp;
                                fscanf(fp,"%i",&temp);
                                buffer[16*y*3+x*3+1] = (unsigned char)temp;
                                fscanf(fp,"%i",&temp);
                                buffer[16*y*3+x*3+2] = (unsigned char)temp;

                        }
                }
                keycounter++;
                tempt.ClearTile();
                tempt.RenderTile(buffer,255,0,255);
                tempt.key = keycounter;
                flat_tiles.push_back(tempt);
        }
        num_tiles++;

 /*	PNGChunk *png_chunk;

	fread(PNGSignature, 8, 1,fp);
    
	//Start reading in chunks
    do
    {
		png_chunk=new PNGChunk;
		
		png_chunk->LoadChunk(fp);

		
		
		
		if(!strcmp(png_chunk->Type, "IEND") || !strcmp(png_chunk->Type, "IHDR") )
			png_chunks.push_back(png_chunk);
		else if(!strcmp(png_chunk->Type, "IDAT"))
		{
			png_chunks.push_back(png_chunk);
			data_length+=png_chunk->Length;
		}

		else delete png_chunk;


    }while(strcmp(png_chunk->Type, "IEND") !=0 );

       //convert image width and height from the IHDR chunk
        int btemp=0;
        num_tiles = 0;

        memcpy(&btemp, &png_chunks[0]->data[0], 1);
        num_tiles += btemp;
        num_tiles = num_tiles << 8;

        memcpy(&btemp, &png_chunks[0]->data[1],1);
        num_tiles += btemp;
        num_tiles = num_tiles << 8;

        memcpy(&btemp, &png_chunks[0]->data[2],1);
        num_tiles += btemp;
        num_tiles = num_tiles << 8;

        memcpy(&btemp, &png_chunks[0]->data[3],1);
        num_tiles += btemp;

        num_tiles /= 16;
	//ConvertIHDR();
	total_height = height;
	total_width = width * num_tiles;

 */
}

void HTFPng::ConvertIHDR()
{
	//convert from big indian to little indian


	int temp=0;
	
	//convert width
	total_width = 0;

	memcpy(&temp, &png_chunks[0]->data[0], 1);
	total_width += temp;
	total_width = total_width << 8;

	memcpy(&temp, &png_chunks[0]->data[1],1);
	total_width+= temp;
	total_width = total_width << 8;

	memcpy(&temp, &png_chunks[0]->data[2],1);
	total_width += temp;
	total_width = total_width << 8;

	memcpy(&temp, &png_chunks[0]->data[3],1);
	total_width += temp;

	//convert height
	temp =0;
	total_height = 0;

	memcpy(&temp, &png_chunks[0]->data[4], 1);
	total_height += temp;
	total_height = total_height << 8;

	memcpy(&temp, &png_chunks[0]->data[5],1);
	total_height += temp;
	total_height = total_height << 8;

	memcpy(&temp, &png_chunks[0]->data[6],1);
	total_height += temp;
	total_height = total_height << 8;

	memcpy(&temp, &png_chunks[0]->data[7],1);
	total_height += temp;
  

}

void HTFPng::CombineImage()
{
	combined_chunk_size = 0;
	for(int i=1; i< png_chunks.size()-1; i++)
		combined_chunk_size += png_chunks[i]->Length;
	combined_chunks = new unsigned char[combined_chunk_size];

	int index = 0;
	for(int i=1; i< png_chunks.size()-1; i++)
	{
		memcpy(&(combined_chunks[index]),png_chunks[i]->data,png_chunks[i]->Length);
		index += png_chunks[i]->Length;
	}
}

void HTFPng::DecompressImage()
{
	decompressed_image = new unsigned char[(total_width*total_height*3)+total_height];
	unsigned long tempi = (total_width*total_height*3)+total_height;
	uncompress(decompressed_image,&tempi,combined_chunks,combined_chunk_size);

}

void HTFPng::GenerateOutputImage()
{
        int rows,last_column,columns;
        rows = (flat_tiles.size() / 64);
        last_column = flat_tiles.size() % 64;
        if(rows == 0) columns = last_column;
        else columns = 64;
        int output_image_size;
//        output_image_size =  (rows*256*16*16*3)+(last_column*16*16*3)+(16*rows);
        if(rows == 0) output_image_size =  (last_column*16*16*3)+(16);
        else if (last_column == 0) output_image_size =  (rows*64*16*16*3)+(16*rows);
        else output_image_size =  ((rows+1)*64*16*16*3)+(16*(rows+1));
//        if(last_column != 0) output_image_size += 16;
	output_image = new unsigned char[output_image_size];

       int rowcount;
        for(rowcount = 0;rowcount < rows;rowcount++)
        {
        	for(int ycount = 0;ycount < 16;ycount++)
        	{
        		for(int tcount = rowcount*64;tcount < (rowcount+1)*64;tcount++)
        		{
        			for(int xcount = 0;xcount < 16;xcount++)
	        		{
	        			output_image[rowcount*(16*16*64*3+16)+(ycount*64*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3] = flat_tiles[tcount].image[ycount*16*3+xcount*3];
			        	output_image[rowcount*(16*16*64*3+16)+(ycount*64*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3+1] = flat_tiles[tcount].image[ycount*16*3+xcount*3+1];
               				output_image[rowcount*(16*16*64*3+16)+(ycount*64*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3+2] = flat_tiles[tcount].image[ycount*16*3+xcount*3+2];
		        	}
        		}
	        }

        }
       if(last_column != 0)
       {
         	for(int ycount = 0;ycount < 16;ycount++)
        	{
        		for(int tcount = rowcount*64;tcount < flat_tiles.size();tcount++)
        		{
        			for(int xcount = 0;xcount < 16;xcount++)
	        		{
	        			output_image[rowcount*(16*16*64*3+16)+(ycount*columns*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3] = flat_tiles[tcount].image[ycount*16*3+xcount*3];
			        	output_image[rowcount*(16*16*64*3+16)+(ycount*columns*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3+1] = flat_tiles[tcount].image[ycount*16*3+xcount*3+1];
               				output_image[rowcount*(16*16*64*3+16)+(ycount*columns*16*3+1*ycount)+((tcount-rowcount*64)*16*3+1)+xcount*3+2] = flat_tiles[tcount].image[ycount*16*3+xcount*3+2];
		        	}
        		}
	        }




       }

      output_image_width = columns*16;
      output_image_height = rowcount*16;
      if(last_column != 0) output_image_height += 16;

}

void HTFPng::CompressImage()
{
	compressed_output_image_size = ((output_image_width*output_image_height*3)+output_image_height) + (((output_image_width*output_image_height*3)+output_image_height)*.01) + 12;
	compressed_output_image = new unsigned char[compressed_output_image_size];
	compress2(compressed_output_image,&compressed_output_image_size,output_image,((output_image_width*output_image_height*3)+output_image_height),9);
}

void HTFPng::FlattenTiles()
{
	unsigned char temptile[16*16*3];
	for(int count = 0;count < flat_tiles.size();count++)
	{
		flat_tiles[count].ClearTile();;
		ExtractTile(temptile,flat_tiles[count].GetLayer1());
		if(flat_tiles[count].GetLayer1H()) HFlip(temptile);
		if(flat_tiles[count].GetLayer1V()) VFlip(temptile);
		flat_tiles[count].RenderTile(temptile,255,0,255);
		ExtractTile(temptile,flat_tiles[count].GetLayer2());
		if(flat_tiles[count].GetLayer2H()) HFlip(temptile);
		if(flat_tiles[count].GetLayer2V()) VFlip(temptile);
		flat_tiles[count].RenderTile(temptile,255,0,255);
		ExtractTile(temptile,flat_tiles[count].GetLayer3());
		if(flat_tiles[count].GetLayer3H()) HFlip(temptile);
		if(flat_tiles[count].GetLayer3V()) VFlip(temptile);
		flat_tiles[count].RenderTile(temptile,255,0,255);

	}
	sort(flat_tiles.begin(),flat_tiles.end(),SortTile);
}

void HTFPng::ExtractTile(unsigned char *arg, int numb)
{
	for(int ycount = 0;ycount < 16;ycount++)
	{
		for(int xcount = 0;xcount < 16;xcount++)
		{
			arg[ycount*16*3 + xcount*3] = decompressed_image[ycount*(total_width*3+1) + (numb*16*3+1) + xcount*3];
			arg[ycount*16*3 + xcount*3+1] = decompressed_image[ycount*(total_width*3+1) + (numb*16*3+1) + xcount*3+1];
			arg[ycount*16*3 + xcount*3+2] = decompressed_image[ycount*(total_width*3+1) + (numb*16*3+1) + xcount*3+2];
		}
	}
}

void HTFPng::HFlip(unsigned char *arg)
{
	int tempr,tempg,tempb;
	for(int ycount = 0;ycount < 16;ycount++)
	{
		for(int xcount = 0;xcount < 8;xcount++)
		{
			tempr = arg[ycount*16*3+xcount*3];
			tempg = arg[ycount*16*3+xcount*3+1];
			tempb = arg[ycount*16*3+xcount*3+2];
			arg[ycount*16*3+xcount*3] = arg[ycount*16*3+(15-xcount)*3];
			arg[ycount*16*3+xcount*3+1] = arg[ycount*16*3+(15-xcount)*3+1];
			arg[ycount*16*3+xcount*3+2] = arg[ycount*16*3+(15-xcount)*3+2];
			arg[ycount*16*3+(15-xcount)*3] = tempr;
			arg[ycount*16*3+(15-xcount)*3+1] = tempg;
			arg[ycount*16*3+(15-xcount)*3+2] = tempb;

		}
	}

}

void HTFPng::VFlip(unsigned char *arg)
{
	int tempr,tempg,tempb;
	for(int ycount = 0;ycount < 8;ycount++)
	{
		for(int xcount = 0;xcount < 16;xcount++)
		{
			tempr = arg[ycount*16*3+xcount*3];
			tempg = arg[ycount*16*3+xcount*3+1];
			tempb = arg[ycount*16*3+xcount*3+2];
			arg[ycount*16*3+xcount*3] = arg[(15-ycount)*16*3+(xcount)*3];
			arg[ycount*16*3+xcount*3+1] = arg[(15-ycount)*16*3+(xcount)*3+1];
			arg[ycount*16*3+xcount*3+2] = arg[(15-ycount)*16*3+(xcount)*3+2];
			arg[(15-ycount)*16*3+(xcount)*3] = tempr;
			arg[(15-ycount)*16*3+(xcount)*3+1] = tempg;
			arg[(15-ycount)*16*3+(xcount)*3+2] = tempb;

		}
	}


}

void HTFPng::CheckKeyVisibility(int &key,int arg1,int arg2)
{
	if(!IsTransparent(arg1)) key = 0;	
	if(!IsTransparent(arg2)) key = 0;	
	
}

void HTFPng::CheckKeyVisibility(int &key,int arg1)
{
	if(!IsTransparent(arg1)) key = 0;	
}

bool HTFPng::IsTransparent(int arg)
{
	bool tempb = false;
	for(int ycount = 0;ycount < 16;ycount++)
	{
		for(int xcount = 0;xcount < 16;xcount++)
		{
			if((decompressed_image[ycount*(total_width*3+1) + arg*16*3 + xcount*3+1] == 255) &&
				(decompressed_image[ycount*(total_width*3+1) + arg*16*3 + xcount*3+2] == 0) &&
				(decompressed_image[ycount*(total_width*3+1) + arg*16*3 + xcount*3+3] == 255))
				tempb = true;
		}
	}
	return tempb;
}
