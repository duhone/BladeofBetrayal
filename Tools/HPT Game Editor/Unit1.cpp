//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "zlib.h"
#include "zconf.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


#pragma link "fontscrollform"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        version = 0.4;

        DialogOptions = new TDialogOptions(Owner);

        AnsiString temp;
        temp.sprintf("HPT Game Editor v%.1f", version);
        Caption = temp;

        TimerAutoSave->Enabled = false;

        DisableFontEdit();
        needtosave = false;

        MessageQue = Messages;

}

        int GetPowerOfTwo(int n)
        {
            int i = 1;

            while (i < n)
            {
                i *= 2;
            }

            if (i == 1)
                return 2;

            return i;
        }
//---------------------------------------------------------------------------

void __fastcall TForm1::NewHGFClick(TObject *Sender)
{
        FILE *temp;
        HGFFile *temphgf;
       char temps[512];


        if(DialogNewHGF->Execute())
        {
                needtosave = true;

                sprintf(temps, "%s Added to project", DialogNewHGF->FileName.c_str());
                DispatchMessage(temps);

                bool duplicate = false;
                for(int i=0; i< HGFFiles->Items->Count; i++)
                {
                        if(strcmp(HGFFiles->Items->Strings[i].c_str(), ExtractFileName(DialogNewHGF->FileName).c_str()) == 0)
                        {
                                duplicate = true;
                                break;
                        }
                }
                if(duplicate)
                {
                        MessageBox(NULL, "You already have a file with this name added to the HGF file list","Error", MB_OK);
                        return;
                }

                //temp = fopen(DialogNewHGF->FileName.c_str(), "wb");
                //if(temp!=NULL)
                //{
                        //MessageBox(NULL, "error", "error", MB_OK);

                        temphgf = new HGFFile;
                        //temphgf->file = temp;
                        temphgf->full_path_name=DialogNewHGF->FileName;
                        temphgf->file_name=ExtractFileName(DialogNewHGF->FileName);

                        HGFFiles->Items->Add(temphgf->file_name.c_str());
                        hgfs.push_back(temphgf);

                //}
        }

}



HGFFile::HGFFile()
{

        //TODO: Add your source code here
}

HGFFile::~HGFFile()
{
        for(int i=0; i<PNGS.size(); i++)
        {
                delete PNGS[i];
        }
        PNGS.clear();
        //fclose(file);//TODO: Add your source code here
}

void __fastcall TForm1::RemoveHGFClick(TObject *Sender)
{
        int index = HGFFiles->ItemIndex;
        vector<HGFFile*>::iterator iter;
        char temps[512];

        if(index >=0)
        {
                needtosave = false;
                iter=hgfs.begin();
                advance(iter, index);

                sprintf(temps, "%s Removed from project", (*iter)->full_path_name.c_str());
                DispatchMessage(temps);

                HGFFiles->Items->Delete(index);
                delete (*iter);
                hgfs.erase(iter);

                HGFImages->Clear();
                width->Clear();
                height->Clear();
                red->Clear();
                green->Clear();
                blue->Clear();
                frameset->Clear();
                framesperset->Clear();
                framerate->Clear();
                framesperset->Clear();
                autoanimate->Checked=false;
                DescriptionEdit->Clear();
                ImageLocEdit->Clear();
                palletentry->Clear();
                hgflocname->Clear();
        }
}

void __fastcall TForm1::HGFFilesClick(TObject *Sender)
{
      addimagebut->Enabled=true;
      removeimagebut->Enabled=true;
      imagelocbut->Enabled=true;
      hgflocbut->Enabled=true;
      applysettingsbut->Enabled=true;

      HGFImages->Clear();
      width->Clear();
      height->Clear();
      red->Clear();
      green->Clear();
      blue->Clear();
      frameset->Clear();
      framesperset->Clear();
      framerate->Clear();
      framesperset->Clear();
      autoanimate->Checked=false;
      DescriptionEdit->Clear();
      ImageLocEdit->Clear();
      palletentry->Clear();
      hgflocname->SetTextBuf(hgfs[HGFFiles->ItemIndex]->full_path_name.c_str());
      for(int i=0; i < hgfs[HGFFiles->ItemIndex]->PNGS.size(); i++)
      {
                HGFImages->Items->Add(hgfs[HGFFiles->ItemIndex]->PNGS[i]->desc.c_str());
      }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::NewGameClick(TObject *Sender)
{
        CloseGameClick(Sender);

        if(DialogNewGame->Execute())
        {
                needtosave=true;
                //proj=fopen(DialogNewGame->FileName.c_str(), "wb");
                //if(proj != NULL)
                //{
                        proj_file = DialogNewGame->FileName;
                        TabSheet->Visible = true;
                        TabSheet->Refresh();

                        MenuHGF->Enabled=true;
                        MenuHSF->Enabled=true;
                        MenuHLFHTF->Enabled=true;
                        CloseGame->Enabled=true;
                        addimagebut->Enabled=false;
                        removeimagebut->Enabled=false;
                        imagelocbut->Enabled=false;
                        hgflocbut->Enabled=false;
                        applysettingsbut->Enabled=false;

                        AnsiString temp;
                        temp.sprintf("HPT Game Editor v%.1f - %s", version, proj_file.c_str());
                        Form1->Caption = temp;
               // }

               //if(DialogOptions->saveproject) TimerAutoSave->Enabled = true;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenGameClick(TObject *Sender)
{
        FILE *proj;
        char temp[512];

        CloseGameClick(Sender);
        if(DialogOpenGame->Execute())
        {
               // proj=fopen(DialogOpenGame->FileName.c_str(), "r+b");
                proj_file = DialogOpenGame->FileName;
                proj=fopen(DialogOpenGame->FileName.c_str(), "rb");
                if(proj != NULL)
                {
                        sprintf(temp, "Loading: %s", DialogOpenGame->FileName.c_str());
                        DispatchMessage(temp);
                        TabSheet->Visible = true;
                        TabSheet->Refresh();

                        MenuHGF->Enabled=true;
                        CloseGame->Enabled=true;
                        addimagebut->Enabled=false;
                        removeimagebut->Enabled=false;
                        imagelocbut->Enabled=false;
                        hgflocbut->Enabled=false;
                        applysettingsbut->Enabled=false;

                        int size;
                        int str_len;
                        char buffer[512];
                        AnsiString ansi_buffer;
                        HGFFile* hgf;
                        HSFFile* hsf;
                        HFFFile* hff;
                        Level* level;

                        fread(&size, sizeof(int), 1, proj);
                        for(int i=0; i<size; i++)
                        {
                                fread(&str_len, sizeof(int), 1, proj);
                                fread(buffer, sizeof(char), str_len, proj);
                                buffer[str_len]='\0';
                                ansi_buffer.sprintf("%s", buffer);

                                hgf = new HGFFile;

                                hgf->full_path_name=ansi_buffer;
                                hgf->file_name=ExtractFileName(ansi_buffer);
                                //hgf->file = fopen(ansi_buffer.c_str(), "r+b");
                                hgf->LoadPrj(proj);

                                hgfs.push_back(hgf);
                                HGFFiles->Items->Add(hgf->file_name);
                        }

                        fread(&size, sizeof(int), 1, proj);
                        for(int i=0; i<size; i++)
                        {
                                fread(&str_len, sizeof(int), 1, proj);
                                fread(buffer, sizeof(char), str_len, proj);
                                buffer[str_len]='\0';
                                ansi_buffer.sprintf("%s", buffer);

                                hsf = new HSFFile;

                                hsf->full_path_name=ansi_buffer;
                                hsf->filename=ExtractFileName(ansi_buffer);
                                hsf->LoadProj(proj);
                                hsfs.push_back(hsf);
                                HSFFiles->Items->Add(hsf->filename);
                        }


                        fread(&size, sizeof(int), 1, proj);
                        for(int i=0; i<size; i++)
                        {
                                fread(&str_len, sizeof(int), 1, proj);
                                fread(buffer, sizeof(char), str_len, proj);
                                buffer[str_len]='\0';
                                ansi_buffer.sprintf("%s", buffer);

                                hff = new HFFFile;

                                hff->full_path_name = ansi_buffer;
                                hff->filename=ExtractFileName(ansi_buffer);
                                hff->LoadProj(proj);
                                hffs.push_back(hff);
                                HFFFiles->Items->Add(hff->filename);
                                HFFFiles->ItemIndex=i;
                                Button2Click(Sender);
                                fontscroll1->Image1->Picture=NULL;
                                HFFFiles->ItemIndex=-1;
                        }

                                //save HLF and HTF information

        fread(&size, sizeof(int), 1, proj);

        for(int i =0; i<size;i++)
        {
                level = new Level();

                level->LoadPrj(proj);

                levels.push_back(level);

                 LevelsList->Items->Add(ExtractFileName(level->level_name.c_str()));
                LevelsList->ItemIndex = 1;

        }


                        fclose(proj);
                }
                AnsiString temp;
                temp.sprintf("HPT Game Editor v%.1f - %s", version, proj_file.c_str());
                Form1->Caption = temp;

              //  if(DialogOptions->saveproject) TimerAutoSave->Enabled = true;
        }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::CloseGameClick(TObject *Sender)
{
        int temp;

        if(needtosave)
        {
                temp = MessageBox(Form1->Handle, "Save changes made to project?", "Close Project", MB_YESNOCANCEL);
                switch(temp)
                {
                case IDYES:
                        SaveGameClick(Sender);
                        break;
                }

        }

        CloseGame->Enabled=false;
        MenuHGF->Enabled=false;
        TabSheet->Visible=false;
        AnsiString temps;
        temps.sprintf("HPT Game Editor v%.1f", version);
        Form1->Caption = temps;
        TimerAutoSave->Enabled=false;

        for(int i=0; i<hsfs.size(); i++)
        {
                delete hsfs[i];
        }
        hsfs.clear();

        for(int i=0; i<hgfs.size(); i++)
        {
                delete hgfs[i];
        }
        hgfs.clear();

        for(int i=0; i<hffs.size(); i++)
        {
                delete hffs[i];
        }
        hffs.clear();

        HGFFiles->Clear();
        HSFFiles->Clear();
        HFFFiles->Clear();

        needtosave = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::addimagebutClick(TObject *Sender)
{
        PNG *temp;
        AnsiString ansi_buffer;

        char* buffer ;
        FILE *fp;

        if(HGFFiles->ItemIndex < 0)
        {
                MessageBox(NULL, "Please select and HGF to add the image to", "Error", MB_OK);
                return;
        }

        if(AddImage->Execute())
        {
                int index = HGFFiles->ItemIndex;

                temp = new PNG;
                hgfs[HGFFiles->ItemIndex]->hgfheader.number_of_images++;

                ansi_buffer = AddImage->FileName;
                fp=fopen(ansi_buffer.c_str(), "rb");
                temp->LoadData(fp);
                //hpt_images.push_back(temp);

                //ansi_buffer=ExtractFileExt(AddImage->FileName);
                //buffer = ansi_buffer.c_str();

                temp->file_name=ExtractFileName(AddImage->FileName);
                temp->full_path_name=AddImage->FileName;
                temp->desc.sprintf("Image%i", hgfs[HGFFiles->ItemIndex]->hgfheader.number_of_images);
                HGFImages->Items->Add(temp->desc.c_str());
                HGFImages->ItemIndex++;
                //ComboBox1->ItemIndex++;
                //ComboBox1Change(Sender);

                hgfs[index]->PNGS.push_back(temp);

                fclose(fp);
        }

}
//---------------------------------------------------------------------------


PNG::PNG()
{
        //TODO: Add your source code here
}

PNG::~PNG()
{
        for(int i=0; i<PNGChunks.size(); i++)
        {
                delete PNGChunks[i];
        }
        PNGChunks.clear();
        //TODO: Add your source code here
}

HPTImageHeader::HPTImageHeader()
{
        color_key_blue=0;
        color_key_red=0;
        color_key_green=0;

        height=0;
        width=0;

        img_height=0;
        img_width=0;

        num_frame_sets=0;
        //TODO: Add your source code here
}

HPTImageHeader::~HPTImageHeader()
{
        //TODO: Add your source code here
}

HGFHeader::HGFHeader()
{
        version = 1;
        number_of_images = 0;
        HGF[0] = 'H';
        HGF[1] = 'G';
        HGF[2] = 'F';
        //TODO: Add your source code here
}


void __fastcall TForm1::HGFImagesChange(TObject *Sender)
{
        int index;
        char buffer[256];
        PNG* png;

        index = HGFImages->ItemIndex;
        if(index >= 0)
        {
                png = hgfs[HGFFiles->ItemIndex]->PNGS[index];
                width->SetTextBuf(itoa(png->image_header.width, buffer, 10));
                height->SetTextBuf(itoa(png->image_header.height, buffer, 10));
                red->SetTextBuf(itoa(png->image_header.color_key_red, buffer, 10));
                green->SetTextBuf(itoa(png->image_header.color_key_green, buffer, 10));
                blue->SetTextBuf(itoa(png->image_header.color_key_blue, buffer, 10));
                frameset->SetTextBuf(itoa(png->image_header.num_frame_sets, buffer, 10));
                png->image_header.SetFramesPerSet(framesperset);
                framerate->Text=FloatToStr(png->image_header.default_frame_rate);
                autoanimate->Checked=png->image_header.default_auto_animate;
                DescriptionEdit->SetTextBuf(png->desc.c_str());
                ImageLocEdit->SetTextBuf(png->full_path_name.c_str());
                palletentry->SetTextBuf(itoa(HGFImages->ItemIndex, buffer, 10));

        }
        else
        {
                width->Clear();
                height->Clear();
                red->Clear();
                green->Clear();
                blue->Clear();
                frameset->Clear();
                framesperset->Clear();
                framerate->Clear();
                framesperset->Clear();
                autoanimate->Checked=false;
                DescriptionEdit->Clear();
                ImageLocEdit->Clear();
                palletentry->Clear();
        }
}
//---------------------------------------------------------------------------


HPTImageHeader::SetFramesPerSet(TEdit* arg)
{
        int j=0;
        char buffer[256];
        int i;
        int temp;
        //arg->GetTextBuf(buffer, 256);
        if(frames_per_set.size() != 0)
        {
                for(i=0;i < frames_per_set.size();i++)
                {
                        temp = frames_per_set[i];
                        itoa(temp, &buffer[j], 10);

                        if(temp < 10)
                        {
                                buffer[j+1]=',';
                                j += 2;
                        }
                        else if(temp < 100)
                        {
                                buffer[j+2]=',';
                                j +=3;
                        }
                        else if(temp < 1000)
                        {
                                buffer[j+3]=',';
                                j +=4;
                        }


                }
                buffer[j]='\0';
                arg->SetTextBuf(buffer);
        }
        else arg->Clear();
        //TODO: Add your source code here
}

HPTImageHeader::GetFramesPerSet(TEdit* arg)
{
        int i=0;
        int len;
        int temp;
        char buffer[256];
        len= arg->GetTextBuf(buffer, 256);

        frames_per_set.clear();

        sscanf(&buffer[i], "%i", &temp);
        frames_per_set.push_back(temp);

        for(i=0; i<len; i++)
        {
                if(buffer[i] == ',')
                {
                        sscanf(&buffer[i+1], "%i", &temp);
                        frames_per_set.push_back(temp);
                }
        }
        //TODO: Add your source code here
}

int PNG::GetPNGWidth()
{
        return image_header.img_width;
}

PNG::LoadData(FILE* fp)
{
        PNGChunk *png_chunk;
        image_header.image_type=2;
        fread(&PNGSignature, 8, 1,fp);
        int btemp=0;
        //Start reading in chunks
        do
        {
                png_chunk=new PNGChunk;

                //read in chunk length
                png_chunk->Length=0;
                btemp=0;

                fread(&btemp, 1, 1,fp);
                png_chunk->Length += btemp;
                png_chunk->Length = png_chunk->Length << 8;

                fread(&btemp, 1, 1,fp);
                png_chunk->Length += btemp;
                png_chunk->Length = png_chunk->Length << 8;

                fread(&btemp, 1,1,fp);
                png_chunk->Length += btemp;
                png_chunk->Length = png_chunk->Length << 8;

                fread(&btemp, 1,1,fp);
                png_chunk->Length += btemp;

                //set up memory for data of chunk
                png_chunk->data = new char[png_chunk->Length];

                //read in Type
                fread(png_chunk->Type, 4, 1, fp);
                png_chunk->Type[4]='\0';

                fread(png_chunk->data, png_chunk->Length, 1, fp);

                fread(&png_chunk->CRC, 4,1,fp);

                if( !strcmp(png_chunk->Type, "IHDR") || !strcmp(png_chunk->Type, "IDAT") || !strcmp(png_chunk->Type, "IEND"))
                        PNGChunks.push_back(png_chunk);



        }while(strcmp(png_chunk->Type, "IEND") !=0 );

        //convert image width and height from the IHDR chunk
        btemp=0;
        image_header.img_width = 0;

        memcpy(&btemp, &PNGChunks[0]->data[0], 1);
        image_header.img_width += btemp;
        image_header.img_width = image_header.img_width << 8;

        memcpy(&btemp, &PNGChunks[0]->data[1],1);
        image_header.img_width += btemp;
        image_header.img_width = image_header.img_width << 8;

        memcpy(&btemp, &PNGChunks[0]->data[2],1);
        image_header.img_width += btemp;
        image_header.img_width = image_header.img_width << 8;

        memcpy(&btemp, &PNGChunks[0]->data[3],1);
        image_header.img_width += btemp;

        //height
        btemp=0;
        memcpy(&btemp, &PNGChunks[0]->data[4],1);
        image_header.img_height +=  btemp;
        image_header.img_height = image_header.img_height << 8;

        memcpy(&btemp, &PNGChunks[0]->data[5],1);
        image_header.img_height +=  btemp;
        image_header.img_height = image_header.img_height << 8;

        memcpy(&btemp, &PNGChunks[0]->data[6],1);
        image_header.img_height +=  btemp;
        image_header.img_height = image_header.img_height << 8;

        memcpy(&btemp, &PNGChunks[0]->data[7],1);
        image_header.img_height +=  btemp;

        //put image into vector
        //hpt_images.push_back(temp);


        //ComboBox1->Items->Add(ExtractFileName(AddImage->FileName));
        //hpt_file_header.number_of_images++;

        //fclose(fp);
}



void __fastcall TForm1::removeimagebutClick(TObject *Sender)
{
        int index;
        vector<PNG*>::iterator iter;

        if(HGFFiles->ItemIndex < 0)
        {
                MessageBox(NULL, "Please select and HGF to remove an image from", "Error", MB_OK);
                return;
        }


        index = HGFImages->ItemIndex;



        if(index >=0)
        {
                iter=hgfs[HGFFiles->ItemIndex]->PNGS.begin();
                advance(iter, index);

                HGFImages->Items->Delete(index);
                delete (*iter);
                hgfs[HGFFiles->ItemIndex]->PNGS.erase(iter);

                HGFImages->SetTextBuf("Current Images");

                width->Clear();
                height->Clear();
                red->Clear();
                green->Clear();
                blue->Clear();
                frameset->Clear();
                framesperset->Clear();
                framerate->Clear();
                autoanimate->Checked=false;
                DescriptionEdit->Clear();
                ImageLocEdit->Clear();
                hgfs[HGFFiles->ItemIndex]->hgfheader.number_of_images--;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::applysettingsbutClick(TObject *Sender)
{
        int index, index2;
        char buffer[512];
        int length;
        PNG* png;
        index = HGFImages->ItemIndex;
        index2 = HGFFiles->ItemIndex;
        if(index >= 0)
        {
                needtosave=true;
                
                png= hgfs[index2]->PNGS[index];

                DescriptionEdit->GetTextBuf(buffer, 512);
                png->desc.sprintf("%s", buffer);
                HGFImages->Items->Delete(index);
                HGFImages->Items->Insert(index, png->desc);
                HGFImages->ItemIndex=index;

                ImageLocEdit->GetTextBuf(buffer, 512);
                png->full_path_name.sprintf("%s", buffer);

                width->GetTextBuf(buffer, 256);
                png->image_header.width=atoi(buffer);

                height->GetTextBuf(buffer, 256);
                png->image_header.height=atoi(buffer);

                red->GetTextBuf(buffer, 256);
                png->image_header.color_key_red=atoi(buffer);

                blue->GetTextBuf(buffer, 256);
                png->image_header.color_key_blue=atoi(buffer);

                green->GetTextBuf(buffer, 256);
                png->image_header.color_key_green=atoi(buffer);

                frameset->GetTextBuf(buffer, 256);
                png->image_header.num_frame_sets=atoi(buffer);

                framerate->GetTextBuf(buffer, 256);
                png->image_header.default_frame_rate=atof(buffer);

                png->image_header.GetFramesPerSet(framesperset);

                png->image_header.default_auto_animate = autoanimate->Checked;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagelocbutClick(TObject *Sender)
{
        if(ImageLocationDialog->Execute())
        {
                ImageLocEdit->Text=ImageLocationDialog->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveHGFClick(TObject *Sender)
{
        AnsiString ansi_buffer;
        PNG *temp;
        FILE *fp;
        //int error=10;
        int size;

        if(HGFFiles->ItemIndex<0)
        {
                MessageBox(NULL, "Please select the HGF you want to save", "Error", MB_OK);
                return;
        }

                ansi_buffer = hgfs[HGFFiles->ItemIndex]->full_path_name;
                fp=fopen(ansi_buffer.c_str(), "wb");
                if(fp != NULL)
                {
                        fwrite(hgfs[HGFFiles->ItemIndex]->hgfheader.HGF, sizeof(char), 3, fp);
                        fwrite(&hgfs[HGFFiles->ItemIndex]->hgfheader.version, sizeof(int), 1, fp);
                        fwrite(&hgfs[HGFFiles->ItemIndex]->hgfheader.number_of_images, sizeof(int), 1, fp);

                        char temps[512];
                        sprintf(temps,"Writing: %s", hgfs[HGFFiles->ItemIndex]->full_path_name.c_str());
                        DispatchMessage(temps);
                        //size = hpt_images.size();
                        for(int i=0; i<hgfs[HGFFiles->ItemIndex]->PNGS.size();i++)
                        {
                                temp = hgfs[HGFFiles->ItemIndex]->PNGS[i];
                                
                                fwrite(&temp->image_header.width,sizeof(int), 1, fp);
                                fwrite(&temp->image_header.height,sizeof(int), 1, fp);
                                fwrite(&temp->image_header.img_width,sizeof(int), 1, fp);
                                fwrite(&temp->image_header.img_height,sizeof(int), 1, fp);

                                fwrite(&temp->image_header.color_key_red, sizeof(int), 1,fp);
                                fwrite(&temp->image_header.color_key_green, sizeof(int), 1, fp);
                                fwrite(&temp->image_header.color_key_blue, sizeof(int), 1, fp);
                                fwrite(&temp->image_header.default_frame_rate, sizeof(float), 1, fp);
                                fwrite(&temp->image_header.default_auto_animate, sizeof(bool), 1, fp);
                                fwrite(&temp->image_header.num_frame_sets, sizeof(int), 1, fp);

                                if(temp->image_header.num_frame_sets > 0)
                                {
                                        for(int j=0; j < temp->image_header.num_frame_sets; j++)
                                        {
                                                fwrite(&temp->image_header.frames_per_set[j], sizeof(int), 1, fp);
                                        }
                                }
                                fwrite(&temp->image_header.image_type, sizeof(int), 1, fp);

                               /* if(temp->image_header.image_type == 1)
                                fwrite(temp->image_data, sizeof(char), (temp->bmp_info_header.biWidth+7)*temp->bmp_info_header.biHeight*3,fp);
                                */
                                if(temp->image_header.image_type ==2)
                                {
                                       int data_size =0;

                                       for(int j=1; j< (temp->PNGChunks.size()-1); j++)
                                                data_size += temp->PNGChunks[j]->Length;



                                        fwrite(&data_size, sizeof(int), 1,fp);
                                        for(int j=1; j < (temp->PNGChunks.size()-1); j++)
                                        {
                                              //fwrite(&temp->PNGChunks[i].Length,4,1,fp);
                                                //fwrite(temp->PNGChunks[i].Type, 4, 1,fp);
                                                fwrite(temp->PNGChunks[j]->data, temp->PNGChunks[j]->Length, 1,fp);
                                         }
                                }
                        }
                        fclose(fp);

             }
             else
             {
                char temps[512];
                sprintf(temps, "ERROR: Unable to open %s for writing", ansi_buffer.c_str());
                DispatchMessage(temps);
//                MessageBox(Form1->Handle, ansi_buffer.c_str(), "Error Opening File For Writing", MB_OK);
             }



}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveAllHGFSClick(TObject *Sender)
{
        for(int i=0; i < hgfs.size(); i++)
        {
                HGFFiles->ItemIndex=i;
                SaveHGFClick(Sender);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::hgflocbutClick(TObject *Sender)
{
        if(DialogHGFLoc->Execute())
        {
                needtosave=true;
                //fclose(hgfs[HGFFiles->ItemIndex]->file);
                //hgfs[HGFFiles->ItemIndex]->file = fopen(DialogHGFLoc->FileName.c_str(), "wb");
                hgfs[HGFFiles->ItemIndex]->full_path_name = DialogHGFLoc->FileName;
                hgfs[HGFFiles->ItemIndex]->file_name = ExtractFileName(DialogHGFLoc->FileName);

                int index = HGFFiles->ItemIndex;
                HGFFiles->Items->Delete(index);
                HGFFiles->Items->Insert(index, hgfs[index]->file_name);
                HGFFiles->ItemIndex=index;

        }

}
//---------------------------------------------------------------------------




TForm1::SaveProject()
{


        //TODO: Add your source code here
}

void HPTWav::LoadData(FILE * fp)
{
        fseek(fp, 40, SEEK_SET);
        fread(&data_size, sizeof(unsigned int),1, fp);

        data = new unsigned short[data_size];

        fread(data, sizeof(unsigned short), data_size, fp);

}

HPTWav::SubtractionFilter()
{
        fil_data = new unsigned short[data_size];

        fil_data[0]=data[0];
        for(int j=1; j< data_size; j++)
        {
                fil_data[j] = data[j] - data[j-1];
        }

 /*       unsigned char *edata = (unsigned char*)fil_data;
        for(int count = 0;count < data_size*2;count+=2)
        {
                char temp;
                temp = edata[count];
                edata[count] = edata[count+1];
                edata[count+1] = temp;
        }  */
}

HPTWav::zlibCompress()
{
        zlib_size = (data_size*2) * .001 + (data_size*2)+ 12;
        zlib_data = new unsigned char[zlib_size];

        compress2(zlib_data, (unsigned long*)&zlib_size, (unsigned char*)fil_data, (unsigned long)data_size*2,9);
}

void HPTWav::WriteData(FILE * fp)
{
        int length = strlen(filename.c_str());
        fwrite(&length, sizeof(int), 1, fp);
        fwrite(filename.c_str(), sizeof(char), length , fp);
}
void __fastcall TForm1::NewHSFClick(TObject *Sender)
{
        FILE *temp;
        HSFFile *temphsf;
        char temps[512];
        if(DialogSaveHSF->Execute())
        {
                needtosave = true;

                sprintf(temps, "%s Added to project", DialogSaveHSF->FileName.c_str());
                DispatchMessage(temps);

                bool duplicate = false;
                for(int i=0; i< HSFFiles->Items->Count; i++)
                {
                        if(strcmp(HSFFiles->Items->Strings[i].c_str(), ExtractFileName(DialogSaveHSF->FileName).c_str()) == 0)
                        {
                                duplicate = true;
                                break;
                        }
                }
                if(duplicate)
                {
                        MessageBox(NULL, "You already have a file with this name added to the HSF file list","Error", MB_OK);
                        return;
                }

                temp = fopen(DialogSaveHSF->FileName.c_str(), "wb");
                if(temp!=NULL)
                {


                        temphsf = new HSFFile;
                       // temphsf->file = temp;
                        temphsf->full_path_name=DialogSaveHSF->FileName;
                        temphsf->filename=ExtractFileName(DialogSaveHSF->FileName);
                        //MessageBox(NULL, "error", "error", MB_OK);
                        HSFFiles->Items->Add(temphsf->filename.c_str());
                        hsfs.push_back(temphsf);

                }
        }
}
//---------------------------------------------------------------------------


HSFFile::HSFFile()
{
        //TODO: Add your source code here
}

HSFFile::~HSFFile()
{
        for(int i=0; i<wavs.size(); i++)
        {
                delete wavs[i];
        }

        //TODO: Add your source code here
}
void __fastcall TForm1::RemoveHSFClick(TObject *Sender)
{
        int index = HSFFiles->ItemIndex;
        vector<HSFFile*>::iterator iter;
        char temps[512];
        if(index >=0)
        {

                needtosave = true;
                iter=hsfs.begin();
                advance(iter, index);

                HSFFiles->Items->Delete(index);

                sprintf(temps, "%s Removed from project", (*iter)->full_path_name.c_str());
                DispatchMessage(temps);
                delete (*iter);
                hsfs.erase(iter);

                HSFSounds->Clear();
                SDescriptionEdit->Clear();
                SoundLocEdit->Clear();
                hsflocname->Clear();
        }
        else
        {
                MessageBox(Form1->Handle, "Select an HSF to delete", "Error", MB_OK);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExitClick(TObject *Sender)
{
        int temp;

        if(needtosave)
        {
                temp = MessageBox(Form1->Handle, "Save changes made to project?", "Quiting", MB_YESNOCANCEL);
                switch(temp)
                {
                case IDYES:
                        SaveGameClick(Sender);
                        break;
                case IDNO:
                        PostQuitMessage(0);
                        break;
                case IDCANCEL:
                        break;
                }

        }
        else PostQuitMessage(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::addsoundbutClick(TObject *Sender)
{
        HPTWav* hptwave;
        AnsiString ansi_buffer;
        FILE *fp;

        if(HSFFiles->ItemIndex <0)
        {
                MessageBox(NULL, "Please select and HSF to add a sound to.", "Error", MB_OK);
                return;
        }

        if( DialogAddSound->Execute())
        {
                hptwave = new HPTWav;

                ansi_buffer=DialogAddSound->FileName;
                hptwave->filename = ansi_buffer;

                fp=fopen(ansi_buffer.c_str(), "rb");

                hptwave->LoadData(fp);
                hptwave->desc=ExtractFileName(DialogAddSound->FileName);
                hsfs[HSFFiles->ItemIndex]->wavs.push_back(hptwave);

                HSFSounds->Items->Add(ExtractFileName(DialogAddSound->FileName));
                HSFSounds->ItemIndex++;
                fclose(fp);

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::removesoundbutClick(TObject *Sender)
{
        if(HSFFiles->ItemIndex <0)
        {
                MessageBox(NULL, "Please select and HSF to delete from", "Error", MB_OK);
                return;
        }

        vector<HPTWav*>::iterator iter;
        int index;

        index = HSFFiles->ItemIndex;

        if(HSFSounds->ItemIndex >= 0)
        {       iter = hsfs[index]->wavs.begin();
                advance(iter, HSFSounds->ItemIndex);

                delete (*iter);
                hsfs[index]->wavs.erase(iter);

                HSFSounds->Items->Delete(index);
                HSFSounds->SetTextBuf("Current Sounds");

                spalletnumber->Clear();
                SDescriptionEdit->Clear();
                SoundLocEdit->Clear();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HSFSoundsChange(TObject *Sender)
{
        HPTWav* wav;
        char buffer[256];
        wav = hsfs[HSFFiles->ItemIndex]->wavs[HSFSounds->ItemIndex];

        spalletnumber->SetTextBuf(itoa(HSFSounds->ItemIndex, buffer, 10));
        SDescriptionEdit->SetTextBuf(wav->desc.c_str());
        SoundLocEdit->SetTextBuf(wav->filename.c_str());


}
//---------------------------------------------------------------------------

void __fastcall TForm1::HSFFilesClick(TObject *Sender)
{
      HSFSounds->Clear();
      SDescriptionEdit->Clear();
      SoundLocEdit->Clear();
      spalletnumber->Clear();
      hsflocname->SetTextBuf(hsfs[HSFFiles->ItemIndex]->full_path_name.c_str());
      for(int i=0; i < hsfs[HSFFiles->ItemIndex]->wavs.size(); i++)
      {
                HSFSounds->Items->Add(hsfs[HSFFiles->ItemIndex]->wavs[i]->desc.c_str());
      }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::sapplysettingbutClick(TObject *Sender)
{
        int index, index2;
        char buffer[512];
        int length;
        HPTWav* wav;
        index = HSFSounds->ItemIndex;
        index2 = HSFFiles->ItemIndex;
        if(index >= 0)
        {
                wav= hsfs[index2]->wavs[index];

                SDescriptionEdit->GetTextBuf(buffer, 512);
                wav->desc.sprintf("%s", buffer);
                HSFSounds->Items->Delete(index);
                HSFSounds->Items->Insert(index, wav->desc);
                HSFSounds->ItemIndex=index;

                SoundLocEdit->GetTextBuf(buffer, 512);
                wav->filename.sprintf("%s", buffer);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::hsflocbutClick(TObject *Sender)
{
        if(DialogHSFLoc->Execute())
        {
                needtosave=true;
                //fclose(hsfs[HSFFiles->ItemIndex]->file);
                //hsfs[HSFFiles->ItemIndex]->file = fopen(DialogHSFLoc->FileName.c_str(), "wb");
                hsfs[HSFFiles->ItemIndex]->full_path_name = DialogHSFLoc->FileName;
                hsfs[HSFFiles->ItemIndex]->filename = ExtractFileName(DialogHSFLoc->FileName);

                int index = HSFFiles->ItemIndex;
                HSFFiles->Items->Delete(index);
                HSFFiles->Items->Insert(index, hsfs[index]->filename);
                HSFFiles->ItemIndex=index;

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::soundlocbutClick(TObject *Sender)
{
        if(DialogSoundLocation->Execute())
        {
                SoundLocEdit->Text=DialogSoundLocation->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveHSFClick(TObject *Sender)
{
        char* HSF = "HSF";
        int   version =1;
        HPTWav* wav;
        int   num_waves;
        FILE *fp;

        if(HSFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select and HSF to save", "Error", MB_OK);
                return;
        }

        num_waves= hsfs[HSFFiles->ItemIndex]->wavs.size();
        fp=fopen(hsfs[HSFFiles->ItemIndex]->full_path_name.c_str(), "wb");

        if(fp != NULL)
        {
                char temps[512];
                sprintf(temps,"Writing: %s", hsfs[HSFFiles->ItemIndex]->full_path_name.c_str());
                DispatchMessage(temps);
                fwrite(HSF, sizeof(char), 3, fp);
                fwrite(&version, sizeof(int), 1, fp);
                fwrite(&num_waves, sizeof(int), 1, fp);

                for(int i=0; i<num_waves; i++)
                {
                        wav=hsfs[HSFFiles->ItemIndex]->wavs[i];
                        wav->SubtractionFilter();
                        wav->zlibCompress();
                        int size = wav->data_size;
                        fwrite(&wav->data_size, sizeof(int), 1, fp);
                        fwrite(&wav->zlib_size, sizeof(int), 1, fp);
                        fwrite(wav->zlib_data, sizeof(unsigned char), wav->zlib_size, fp);
                }
                fclose(fp);
        }
        else
        {
                char temps[512];
                sprintf(temps, "ERROR: Unable to open %s for writing", hsfs[HSFFiles->ItemIndex]->full_path_name.c_str());
                DispatchMessage(temps);
        }
                //MessageBox(Form1->Handle, hsfs[HSFFiles->ItemIndex]->full_path_name.c_str(), "Error Opening File For Writing", MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveAllHSFSClick(TObject *Sender)
{
        for(int i=0; i < hsfs.size(); i++)
        {
                HSFFiles->ItemIndex=i;
                SaveHSFClick(Sender);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveGameClick(TObject *Sender)
{
        needtosave=false;

        //save hgf stuff
        int temp;
        FILE *proj;
        proj = fopen(proj_file.c_str(), "wb");

        char temps[512];

        if(proj != NULL)
        {
        sprintf(temps, "Saving: %s", proj_file.c_str());
        DispatchMessage(temps);

        temp = hgfs.size();
        fwrite(&temp, sizeof(int), 1 , proj);
        for(int i=0; i<hgfs.size(); i++)
        {
                temp =hgfs[i]->full_path_name.Length();
                fwrite(&temp , sizeof(int), 1, proj );
                fwrite(hgfs[i]->full_path_name.c_str(), sizeof(char), temp, proj);
                hgfs[i]->SavePrj(proj);
        }

        temp = hsfs.size();
        fwrite(&temp, sizeof(int), 1, proj);
        for(int i=0; i<hsfs.size(); i++)
        {
                temp = hsfs[i]->full_path_name.Length();
                fwrite(&temp, sizeof(int), 1, proj);
                fwrite(hsfs[i]->full_path_name.c_str(), sizeof(char), temp , proj);
                hsfs[i]->SaveProj(proj);
        }

        temp = hffs.size();
        fwrite(&temp, sizeof(int), 1, proj);
        for(int i =0; i<hffs.size(); i++)
        {
                temp = hffs[i]->full_path_name.Length();
                fwrite(&temp, sizeof(int), 1, proj);
                fwrite(hffs[i]->full_path_name.c_str(), sizeof(char), temp , proj);
                hffs[i]->SaveProj(proj);
        }

        //save HLF and HTF information
        temp = levels.size();
        fwrite(&temp, sizeof(int), 1, proj);

        for(int i =0; i<levels.size();i++)
        {
                levels[i]->SavePrj(proj);
        }

        fclose(proj);
        }
        else
        {
                sprintf(temps, "ERROR: unable to open %s for writing", proj_file.c_str());
                DispatchMessage(temps);
        }
}
//---------------------------------------------------------------------------


void Level::LoadPrj(FILE *fp)
{
        int temp;
        char buffer[512];

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        level_name = buffer;

        OutputDebugString(level_name.c_str());

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        map_data = buffer;

        OutputDebugString(map_data.c_str());

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        tileimage_layer1 = buffer;

        OutputDebugString(tileimage_layer1.c_str());

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        tiledata_layer1 = buffer;

        OutputDebugString(tiledata_layer1.c_str());

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        tileimage_layer2 = buffer;

        OutputDebugString(tileimage_layer2.c_str());

        fread(&temp, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), temp, fp);
        buffer[temp] = '\0';
        tiledata_layer2 = buffer;

        OutputDebugString(tiledata_layer2.c_str());

        fread(&num_frontlayer_tiles, sizeof(int), 1, fp);
        fread(&num_backlayer_tiles, sizeof(int), 1, fp);
}

void Level::SavePrj(FILE *fp)
{
        int temp;

        OutputDebugString(level_name.c_str());

        temp = level_name.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(level_name.c_str(), sizeof(char), temp, fp);
        OutputDebugString(level_name.c_str());

        temp = map_data.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(map_data.c_str(), sizeof(char), temp, fp);
        OutputDebugString(map_data.c_str());

        temp = tileimage_layer1.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(tileimage_layer1.c_str(), sizeof(char), temp, fp);
        OutputDebugString(tileimage_layer1.c_str());

        temp = tiledata_layer1.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(tiledata_layer1.c_str(), sizeof(char), temp, fp);
        OutputDebugString(tiledata_layer1.c_str());

        temp = tileimage_layer2.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(tileimage_layer2.c_str(), sizeof(char), temp, fp);
        OutputDebugString(tileimage_layer2.c_str());

        temp = tiledata_layer2.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(tiledata_layer2.c_str(), sizeof(char), temp, fp);
        OutputDebugString(tiledata_layer2.c_str());

        fwrite(&num_frontlayer_tiles, sizeof(int), 1, fp);
        fwrite(&num_backlayer_tiles, sizeof(int), 1, fp);
}

HGFFile::SavePrj(FILE *fp)
{
        PNG *temp;
        int version =1;
        int size = PNGS.size();

        //fp=fopen(SaveHgtDialog->FileName.c_str(), "wb");

        fwrite(&size, sizeof(int), 1, fp);
        for(int i =0; i<size; i++)
        {
               temp = PNGS[i];
               int str_len = temp->full_path_name.Length();
               fwrite(&str_len, sizeof(int), 1, fp);
               fwrite(temp->full_path_name.c_str(), sizeof(char), str_len, fp);

               str_len = temp->desc.Length();
               fwrite(&str_len, sizeof(int), 1, fp);
               fwrite(temp->desc.c_str(), sizeof(char), str_len, fp);


               fwrite(&temp->image_header.width,sizeof(int), 1, fp);
               fwrite(&temp->image_header.height,sizeof(int), 1, fp);
             //fwrite(&temp->image_header.img_width,sizeof(int), 1, fp);
             //fwrite(&temp->image_header.img_height,sizeof(int), 1, fp);

               fwrite(&temp->image_header.color_key_red, sizeof(int), 1,fp);
               fwrite(&temp->image_header.color_key_blue, sizeof(int), 1, fp);
               fwrite(&temp->image_header.color_key_green, sizeof(int), 1, fp);
               fwrite(&temp->image_header.default_frame_rate, sizeof(float), 1, fp);
               fwrite(&temp->image_header.default_auto_animate, sizeof(bool), 1, fp);
               fwrite(&temp->image_header.num_frame_sets, sizeof(int), 1, fp);

               if(temp->image_header.num_frame_sets > 0)
               {
                      for(int j=0; j < temp->image_header.num_frame_sets; j++)
                      {
                             fwrite(&temp->image_header.frames_per_set[j], sizeof(int), 1, fp);
                      }
                }
                //fwrite(&temp->image_header.image_type, sizeof(int), 1, fp);
        }
        //TODO: Add your source code here
}

HGFFile::LoadPrj(FILE* fp)
{
        int size;
        FILE *fp_image;
        int str_len;
        char buffer[512];
        AnsiString ansi_buffer;
        AnsiString fullpathname;
        AnsiString description;
        PNG *hptimage;

       // int btemp=0;
       for(int i=0; i<PNGS.size(); i++)
       {
                delete PNGS[i];
       }
       PNGS.clear();

       hgfheader.number_of_images=0;

       fread(&size, sizeof(int), 1, fp);
       hgfheader.number_of_images=size;
       for(int i=0; i<size; i++)
       {
                fp_image = NULL;

                fread(&str_len, sizeof(int), 1, fp);
                fread(buffer, sizeof(char), str_len, fp);
                buffer[str_len]='\0';
                ansi_buffer.sprintf("%s", buffer);
                fullpathname = ansi_buffer;

                fread(&str_len, sizeof(int), 1, fp);
                fread(buffer, sizeof(char), str_len, fp);
                buffer[str_len]='\0';
                ansi_buffer.sprintf("%s", buffer);
                description = ansi_buffer;


                hptimage = new PNG;

                fread(&hptimage->image_header.width,sizeof(int), 1, fp);
                fread(&hptimage->image_header.height,sizeof(int), 1, fp);

                fread(&hptimage->image_header.color_key_red, sizeof(int), 1,fp);
                fread(&hptimage->image_header.color_key_blue, sizeof(int), 1, fp);
                fread(&hptimage->image_header.color_key_green, sizeof(int), 1, fp);
                fread(&hptimage->image_header.default_frame_rate, sizeof(float), 1, fp);
                fread(&hptimage->image_header.default_auto_animate, sizeof(bool), 1, fp);
                fread(&hptimage->image_header.num_frame_sets, sizeof(int), 1, fp);
                if(hptimage->image_header.num_frame_sets > 0)
                {
                        int frames;
                        for(int j=0; j < hptimage->image_header.num_frame_sets; j++)
                        {
                                fread(&frames, sizeof(int), 1, fp);
                                hptimage->image_header.frames_per_set.push_back(frames);
                        }
                }
                hptimage->file_name=ExtractFileName(fullpathname);
                hptimage->full_path_name=fullpathname;
                hptimage->desc = description;

                fp_image = fopen(fullpathname.c_str(), "rb");
                if(fp_image != NULL)
                {

                        //hptimage->LoadData(fp_image);
                        fclose(fp_image);
                }
                else
                {
                        char temps[512];
                        sprintf(temps, "ERROR: unable to open file %s located in project file %s", fullpathname.c_str(), full_path_name.c_str());
                        DispatchMessage(temps);
//                        MessageBox(Form1->Handle, fullpathname.c_str(), "File Not Found", MB_OK);
                }
                PNGS.push_back(hptimage);
        }


        //TODO: Add your source code here
}

HSFFile::SaveProj(FILE * fp)
{
        int size = wavs.size();
        int temp;

        fwrite(&size, sizeof(int), 1, fp);
        for(int i=0; i<wavs.size(); i++)
        {
                temp = wavs[i]->filename.Length();
                fwrite(&temp, sizeof(int), 1, fp);
                fwrite(wavs[i]->filename.c_str(), sizeof(char), temp , fp);

                temp = wavs[i]->desc.Length();
                fwrite(&temp, sizeof(int), 1, fp);
                fwrite(wavs[i]->desc.c_str(), sizeof(char), temp , fp);
        }

        //TODO: Add your source code here
}

HSFFile::LoadProj(FILE * fp)
{
        FILE *fp_sound;
        int size;
        HPTWav *hptwav;
        int str_len;
        char buffer[512];
        AnsiString ansi_buffer;

        AnsiString desc;
        AnsiString fullpathname;

        for(int i=0; i<wavs.size(); i++)
        {
                delete wavs[i];
        }
        wavs.clear();


        fread(&size, sizeof(int), 1, fp);
        for(int i=0; i<size; i++)
        {
                fread(&str_len, sizeof(int), 1, fp);
                fread(buffer, sizeof(char), str_len, fp);
                buffer[str_len]='\0';
                ansi_buffer.sprintf("%s", buffer);
                fullpathname = ansi_buffer;

                fread(&str_len, sizeof(int), 1, fp);
                fread(buffer, sizeof(char), str_len, fp);
                buffer[str_len]='\0';
                ansi_buffer.sprintf("%s", buffer);
                desc = ansi_buffer;

                hptwav = new HPTWav;
                hptwav->desc=desc;
                hptwav->filename=fullpathname;

                fp_sound = fopen(fullpathname.c_str(), "rb");
                if(fp_sound != NULL)
                {
                      //HSFFiles->Items->Add(ExtractFileName(ansi_buffer));
                        hptwav->LoadData(fp_sound);
                        fclose(fp_sound);

                }
                else
                {
                        //MessageBox(Form1->Handle, full_path_name.c_str(), "File Not Found", MB_OK);
                        char temps[512];
                        sprintf(temps, "ERROR: unable to open file %s located in project file %s", fullpathname.c_str(), full_path_name.c_str());
                        DispatchMessage(temps);
                }
                wavs.push_back(hptwav);
        }
                //TODO: Add your source code here
}





void __fastcall TForm1::choosefontbutClick(TObject *Sender)
{
    if(HFFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select an HFF to edit", "Error", MB_OK);
                return;
        }
   if(hffs[HFFFiles->ItemIndex]->font != NULL) FontDialog1->Font = hffs[HFFFiles->ItemIndex]->font;
   else hffs[HFFFiles->ItemIndex]->font = new TFont;

   if(FontDialog1->Execute())
   {
        needtosave=true;
        hffs[HFFFiles->ItemIndex]->font->Assign(FontDialog1->Font);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveHFFClick(TObject *Sender)
{
        if(HFFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select an HFF to save.", "Error", MB_OK);
                return;
        }

        // retrieve the currently selected HFF file
        HFFFile *hff = hffs[HFFFiles->ItemIndex];

        // do power of 2's function on bwidth and bheight
        int pwWidth = GetPowerOfTwo(hff->bwidth);
        int pwHeight = GetPowerOfTwo(hff->bheight);

        // notify logging that an hff file is being written
        char temps[512];
        sprintf(temps,"Writing: %s", hff->full_path_name.c_str());
        DispatchMessage(temps);

        // Calculate the entire file size (including header)
        // ** Update to include width padding and height padding

        //int filesize = ((hff->bwidth * hff->bheight)/4) + 1; // size of actual font data
        int filesize = ((pwWidth * pwHeight)/4) + 1;

        filesize += 4*95; // size of the character offsets array (distance from left of bitmap)
        filesize += 4*12; // rest of header info
        filesize += 3;    //HFF

        // possibly for use with a generated png image (windows bitmap nonsense)
        int row = hff->bwidth;
        int extrabytes = 4-((hff->bwidth*3)%4);
        row += extrabytes;

        // file type and version
        char filetype[3] = {'H','F','F'};
        int fileversion = 1;

        //
       	HANDLE filehandle = CreateFile(hffs[HFFFiles->ItemIndex]->full_path_name.c_str(),GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS	,FILE_ATTRIBUTE_NORMAL,NULL);
	if(filehandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"name","could not open requested HFF file",MB_OK);
		return;
	}

        //
	HANDLE filemapping = CreateFileMapping(filehandle,NULL,PAGE_READWRITE,0,filesize,NULL);
	if(filemapping == NULL)
	{
		MessageBox(NULL,"name","could not map requested HGF file",MB_OK);
		return;
	}

        //
	void *filepointer = MapViewOfFile(filemapping,FILE_MAP_WRITE,0,0,0);
	if(filepointer == NULL)
	{
		MessageBox(NULL,"name","could not view requested HGF file",MB_OK);
		return;
	}

        // memory mapped file writing
        unsigned char *fpntr = (unsigned char*)filepointer;
        memcpy(fpntr,filetype,3); // HFF
        fpntr += 3;
        memcpy(fpntr,&fileversion,4);
        fpntr += 4;
        memcpy(fpntr,&hff->bwidth,4);
        fpntr += 4;
        memcpy(fpntr,&hff->bheight,4);
        fpntr += 4;
        memcpy(fpntr,&hff->keyred,4);
        fpntr += 4;
        memcpy(fpntr,&hff->keygreen,4);
        fpntr += 4;
        memcpy(fpntr,&hff->keyblue,4);
        fpntr += 4;
        memcpy(fpntr,&hff->colorred,4);
        fpntr += 4;
        memcpy(fpntr,&hff->colorgreen,4);
        fpntr += 4;
        memcpy(fpntr,&hff->colorblue,4);
        fpntr += 4;
        memcpy(fpntr,&hff->fringred,4);
        fpntr += 4;
        memcpy(fpntr,&hff->fringgreen,4);
        fpntr += 4;
        memcpy(fpntr,&hff->fringblue,4);
        fpntr += 4;
        memcpy(fpntr,hff->charwidths,95*4);
        fpntr += 95*4;

        unsigned char *bitsptr;

        // number of bits in the final byte
        int extrabits = (hff->bwidth*hff->bheight)%8;

        int keytemp = 0;
        int colortemp = 0;
	int fringetemp = 0;
        int bitsofar = 0;
        unsigned char curbit = 0;

        // transparent colorkey
        keytemp += hff->keyblue;
        keytemp = keytemp<<8;
        keytemp += hff->keygreen;
        keytemp  = keytemp<<8;
        keytemp += hff->keyred;

        // fringe color
        fringetemp += hff->fringblue;
        fringetemp = fringetemp<<8;
        fringetemp += hff->fringgreen;
        fringetemp = fringetemp<<8;
        fringetemp += hff->fringred;


        // writes out the image (2bpp) (reads from image that was generated)



        // ** ADD Extra rows (Prerows) (Duplicate both loops)
        int preheight = (pwHeight - hff->bheight)/2;
        int postheight = (pwHeight - hff->bheight)/2;
        if ((pwHeight - hff->bheight) & 1)
            postheight++;

        for(int count = 0;count < preheight;count++)
        {
           for(int count2 = 0;count2 < pwWidth;count2++)
           {
                 curbit = curbit | 0; // *** USE ONLY THIS CHUNK

                //*** Keep as is in all new loops (keeps track of bits)
                 bitsofar += 2;
                 if(bitsofar == 8)
                 {
                   (*fpntr) = curbit;
                   bitsofar = 0;
                   curbit = 0;
                   fpntr++;
                 }
                 else
                 {
                  curbit = curbit << 2;
                 }
           }
        }

        for(int count = 0;count < hff->bheight;count++)
        {
           bitsptr = (unsigned char*)hff->tbitmap->ScanLine[count];
           for(int count2 = 0;count2 < hff->bwidth;count2++)
           {
                // reads the source color
                //** Get rid of this chunk
                int tempbit;
                colortemp = 0;
                colortemp += *bitsptr;
                bitsptr++;
                colortemp = colortemp<<8;
                colortemp += *bitsptr;
                bitsptr++;
                colortemp = colortemp<<8;
                colortemp += *bitsptr;
                bitsptr++;

                // write output based on 3 color types
                if(colortemp == keytemp)
                {
                 curbit = curbit | 0; // *** USE ONLY THIS CHUNK
                }
                else if(colortemp == fringetemp)
                {
                 curbit = curbit | 1;
                }
		else
		{
		 curbit = curbit | 2;
		}

                //*** Keep as is in all new loops (keeps track of bits)
                 bitsofar += 2;
                 if(bitsofar == 8)
                 {
                   (*fpntr) = curbit;
                   bitsofar = 0;
                   curbit = 0;
                   fpntr++;
                 }
                 else
                 {
                  curbit = curbit << 2;
                 }
           }

           // ** Add extra columns (copy inner loop only)
           for(int count2 = 0;count2 < pwWidth-hff->bwidth;count2++)
           {
                 curbit = curbit | 0; // *** USE ONLY THIS CHUNK

                //*** Keep as is in all new loops (keeps track of bits)
                 bitsofar += 2;
                 if(bitsofar == 8)
                 {
                   (*fpntr) = curbit;
                   bitsofar = 0;
                   curbit = 0;
                   fpntr++;
                 }
                 else
                 {
                  curbit = curbit << 2;
                 }
           }

        }

        // ** ADD Extra rows (Postrows) (Duplicate both loops)
        for(int count = 0;count < postheight;count++)
        {
           for(int count2 = 0;count2 < pwWidth;count2++)
           {
                 curbit = curbit | 0; // *** USE ONLY THIS CHUNK

                //*** Keep as is in all new loops (keeps track of bits)
                 bitsofar += 2;
                 if(bitsofar == 8)
                 {
                   (*fpntr) = curbit;
                   bitsofar = 0;
                   curbit = 0;
                   fpntr++;
                 }
                 else
                 {
                  curbit = curbit << 2;
                 }
           }
        }

        // writes out the final byte
        if(bitsofar > 0)
        {
          curbit = curbit << (8 - bitsofar);
          (*fpntr) = curbit;
        }

        UnmapViewOfFile(filepointer);
	CloseHandle(filemapping);
	CloseHandle(filehandle);

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm1::KeyRedEditChange(TObject *Sender)
{
        if(HFFFiles->ItemIndex<0) return;

        int Size = KeyRedEdit->GetTextLen(); //Get length of string in Edit1
        HFFFile *hff = hffs[HFFFiles->ItemIndex];

        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        KeyRedEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->keyred);
        if(hff->keyred < 0) hff->keyred = 0;
        if(hff->keyred > 255) hff->keyred = 255;

         //sprintf(Buffer,"%d",keyred);
        //KeyRedEdit->SetTextBuf(Buffer);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyRedEditExit(TObject *Sender)
{


     AnsiString temp;
     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->keyred);

     KeyRedEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyGreenEditChange(TObject *Sender)
{
        if(HFFFiles->ItemIndex<0) return;
       int Size = KeyGreenEdit->GetTextLen(); //Get length of string in Edit1
       HFFFile *hff = hffs[HFFFiles->ItemIndex];
        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        KeyGreenEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->keygreen);
        if(hff->keygreen < 0) hff->keygreen = 0;
        if(hff->keygreen > 255) hff->keygreen = 255;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyGreenEditExit(TObject *Sender)
{



   AnsiString temp;
     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->keygreen);

     KeyGreenEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyBlueEditChange(TObject *Sender)
{

              if(HFFFiles->ItemIndex<0) return;
      int Size = KeyBlueEdit->GetTextLen(); //Get length of string in Edit1
      HFFFile *hff = hffs[HFFFiles->ItemIndex];
        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        KeyBlueEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->keyblue);
        if(hff->keyblue < 0) hff->keyblue = 0;
        if(hff->keyblue > 255) hff->keyblue = 255;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorRedEditChange(TObject *Sender)
{
              if(HFFFiles->ItemIndex<0) return;
      int Size = ColorRedEdit->GetTextLen(); //Get length of string in Edit1
      HFFFile *hff = hffs[HFFFiles->ItemIndex];
        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        ColorRedEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->colorred);
        if(hff->colorred < 0) hff->colorred = 0;
        if(hff->colorred > 255) hff->colorred = 255;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorGreenEditChange(TObject *Sender)
{

               if(HFFFiles->ItemIndex<0) return;

      int Size = ColorGreenEdit->GetTextLen(); //Get length of string in Edit1
       HFFFile *hff = hffs[HFFFiles->ItemIndex];
        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        ColorGreenEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->colorgreen);
        if(hff->colorgreen < 0) hff->colorgreen = 0;
        if(hff->colorgreen > 255) hff->colorgreen = 255;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorBlueEditChange(TObject *Sender)
{

              if(HFFFiles->ItemIndex<0) return;
      int Size = ColorBlueEdit->GetTextLen(); //Get length of string in Edit1
      HFFFile *hff = hffs[HFFFiles->ItemIndex];

        Size++;                      //Add room for null character
        //if(Size < 10) Size = 10;
        char *Buffer = new char[Size];  //Creates Buffer dynamic variable

        ColorBlueEdit->GetTextBuf(Buffer,Size); //Puts Edit1->Text into Buffer

        sscanf(Buffer,"%d",&hff->colorblue);
        if(hff->colorblue < 0) hff->colorblue = 0;
        if(hff->colorblue > 255) hff->colorblue = 255;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyBlueEditExit(TObject *Sender)
{

    AnsiString temp;


     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->keyblue);

     KeyBlueEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorRedEditExit(TObject *Sender)
{
           if(HFFFiles->ItemIndex <0)
           {
                ColorRedEdit->Text.sprintf("0");
                return;
           }
   AnsiString temp;
     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->colorred);

     ColorRedEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorGreenEditExit(TObject *Sender)
{
           if(HFFFiles->ItemIndex <0)
           {
                ColorGreenEdit->Text.sprintf("0");
                return;
           }
   AnsiString temp;
     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->colorgreen);

     ColorGreenEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ColorBlueEditExit(TObject *Sender)
{
           if(HFFFiles->ItemIndex <0)
           {
                KeyBlueEdit->Text.sprintf("0");
                return;
           }

   AnsiString temp;
     temp.sprintf("%d",hffs[HFFFiles->ItemIndex]->colorblue);

     ColorBlueEdit->Text = temp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        if(HFFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select an HFF to create font for", "Error", MB_OK);
                return;
        }

        HFFFile *hff = hffs[HFFFiles->ItemIndex];
        if(hff->font == NULL) return;
        TEXTMETRIC textp;
        HWND hwnd = Form1->Handle;
        HDC hdc;
        hdc = GetDC(hwnd);
        SelectObject(hdc,hff->font->Handle);
        GetTextMetrics(hdc,&textp);
        if((textp.tmPitchAndFamily & TMPF_TRUETYPE) == TMPF_TRUETYPE)
        {
                ABC tempabc[95];
                GetCharABCWidths(hdc,' ','~',tempabc);
                for(int count = 0;count < 95;count++)
                {
                        hff->charwidths[count] = tempabc[count].abcA + tempabc[count].abcB + tempabc[count].abcC;
                }
        }
        else
        {
                GetCharWidth32(hdc,' ','~',hff->charwidths);
        }
        /*for(int count = 0;count < 95;count++)
        {
           hff->charwidths[count] += 2;
        }  */
        ReleaseDC(hwnd,hdc);
        hff->bwidth = textp.tmMaxCharWidth*95;
        hff->bheight = textp.tmHeight;
        hff->bwidth = 0;
        for(int count = 0;count < 95;count++)
        {
          if(hff->charwidths[count] > hff->bwidth) hff->bwidth =  hff->charwidths[count];
        }
        hff->bwidth += 4;
        hff->bwidth *= 95;
        hff->binfo.biSize = sizeof(BITMAPINFOHEADER);
        hff->binfo.biWidth = hff->bwidth;
        hff->binfo.biHeight = hff->bheight;
        hff->binfo.biPlanes = 1;
        hff->binfo.biBitCount = 24;
        hff->binfo.biCompression = BI_RGB;
        hff->binfo.biSizeImage = 0;
        hff->binfo.biXPelsPerMeter = 0;
        hff->binfo.biYPelsPerMeter = 0;
        hff->binfo.biClrUsed = 0;
        hff->binfo.biClrImportant = 0;

        HBITMAP hbitmap = CreateDIBSection(NULL,(BITMAPINFO*) &hff->binfo,0,&(void*)hff->bits,NULL,0);

        hdc = CreateCompatibleDC(NULL);
        SelectObject(hdc,hbitmap);
        RECT rect;
        rect.left = 0;
        rect.right = hff->bwidth;
        rect.top = 0;
        rect.bottom = hff->bheight;
        HBRUSH brush;
        brush = CreateSolidBrush(RGB(hff->keyred,hff->keygreen,hff->keyblue));
        SelectObject(hdc,brush);
        FillRect(hdc,&rect,&brush);
        char tempc[2];
        tempc[1] = 0;
        tempc[0] = 32;
        int width1 = hff->bwidth/95;
        SelectObject(hdc,hff->font->Handle);
        SetBkMode(hdc,TRANSPARENT);
        SetTextColor(hdc,RGB(hff->colorred,hff->colorgreen,hff->colorblue));
        for(int count = 0;count < 95;count++)
        {
                rect.left = count*width1;
                rect.right = count*width1-1+width1;
                DrawText(hdc,tempc,1,&rect,DT_CENTER | DT_NOPREFIX | DT_VCENTER);
                tempc[0]++;
        }


        DeleteDC(hdc);
        DeleteObject(&brush);

        hff->tbitmap->Handle = hbitmap;
        //int skipbytes;
        //skipbytes = 4 - (hff->bwidth*3)%4;
        //if(skipbytes == 4) skipbytes = 0;
        unsigned char *temp_bits;
        unsigned char *temp_bits_prev;
        unsigned char *temp_bits_next;
        //temp_bits += 3;
        for(int count = 0;count < hff->bheight;count++)
        {
                temp_bits = (unsigned char*)hff->tbitmap->ScanLine[count];
                if(count != 0) temp_bits_prev = (unsigned char*)hff->tbitmap->ScanLine[count-1];
                if(count != (hff->bheight-1)) temp_bits_next = (unsigned char*)hff->tbitmap->ScanLine[count+1];
                for(int count2 = 0;count2 < hff->bwidth;count2++)
                {
                       if((count2 == 0))
                        {
                                temp_bits += 3;
                                 temp_bits_prev += 3;
                       temp_bits_next += 3;
                                continue;
                        }
                        if((count2 == hff->binfo.biWidth-1))
                        {
                                temp_bits += 3;
                                 temp_bits_prev += 3;
                       temp_bits_next += 3;
                                continue;
                        }
                        if((temp_bits[0] == hff->keyblue) && (temp_bits[1] == hff->keygreen) && (temp_bits[2] == hff->keyred))
                        {
                                bool fringe = false;
                                if(count2 != 0)
                                {
                                        if((temp_bits[-3] == hff->colorblue) && (temp_bits[-2] == hff->colorgreen) && (temp_bits[-1] == hff->colorred))
                                        {
                                                fringe = true;
                                        }
                                }
                                if((temp_bits[3] == hff->colorblue) && (temp_bits[4] == hff->colorgreen) && (temp_bits[5] == hff->colorred))
                                {
                                        fringe = true;
                                }
                                if(count != 0)
                                {
                                        if((temp_bits_prev[0] == hff->colorblue) && (temp_bits_prev[1] == hff->colorgreen) && (temp_bits_prev[2] == hff->colorred))
                                        {
                                                fringe = true;
                                        }
                                }
                                if(count != (hff->bheight - 1))
                                {
                                       if((temp_bits_next[0] == hff->colorblue) && (temp_bits_next[1] == hff->colorgreen) && (temp_bits_next[2] == hff->colorred))
                                       {
                                                fringe = true;
                                       }

                                }
                                if(fringe)
                                {
                                        temp_bits[0] = hff->fringblue;
                                        temp_bits[1] = hff->fringgreen;
                                        temp_bits[2] = hff->fringred;
                                }
                        }
                        temp_bits += 3;
                       temp_bits_prev += 3;
                       temp_bits_next += 3;
                }
                //temp_bits += skipbytes;
        }


        
        hff->tpic->Assign(hff->tbitmap);

       fontscroll1->Image1->Picture = hff->tpic;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm1::AddFont1Click(TObject *Sender)
{
        FILE *temp;
        HFFFile *temphff;
        char temps[512];
        if(DialogNewHFF->Execute())
        {
                needtosave = true;

                sprintf(temps, "%s Added to project", DialogNewHFF->FileName.c_str());
                DispatchMessage(temps);
                bool duplicate = false;
                for(int i=0; i< HFFFiles->Items->Count; i++)
                {
                        if(strcmp(HFFFiles->Items->Strings[i].c_str(), ExtractFileName(DialogNewHFF->FileName).c_str()) == 0)
                        {
                                duplicate = true;
                                break;
                        }
                }
                if(duplicate)
                {
                        MessageBox(NULL, "You already have a file with this name added to the HGF file list","Error", MB_OK);
                        return;
                }

                //temp = fopen(DialogNewHGF->FileName.c_str(), "wb");
                //if(temp!=NULL)
                //{
                        //MessageBox(NULL, "error", "error", MB_OK);

                        temphff = new HFFFile;
                        //temphgf->file = temp;
                        temphff->full_path_name=DialogNewHFF->FileName;
                        temphff->filename=ExtractFileName(DialogNewHFF->FileName);

                        //temphff->font = NULL;
                        temphff->tbitmap = new Graphics::TBitmap;
                        temphff->tpic = new Graphics::TPicture;

                        HFFFiles->Items->Add(temphff->filename.c_str());
                        hffs.push_back(temphff);

                //}
        }
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------



HFFFile::HFFFile()
{
        bheight =0;
        bwidth =0;
        colorblue=0;
        colorgreen=0;
        colorred =0;
        fringred=0;
        fringblue=0;
        fringgreen=0;
        
        font = NULL;
        keyblue=0;
        keygreen=0;
        keyred=0;
        tbitmap = NULL;
        tpic = NULL;

        //TODO: Add your source code here
}

void __fastcall TForm1::RemoveHFF1Click(TObject *Sender)
{
        if(HFFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select an HFF to delete", "Error", MB_OK);
                DisableFontEdit();
                return;
        }

        needtosave = true;
        HFFFile *temphff;
        vector<HFFFile*>::iterator iter;
        int index = HFFFiles->ItemIndex;

        HFFFiles->Items->Delete(index);
        temphff = hffs[index];

        
        char temps[512];
        sprintf(temps, "%s Removed from project", temphff->full_path_name.c_str());
        DispatchMessage(temps);

        delete temphff;

        iter = hffs.begin();
        advance(iter, index);



        hffs.erase(iter);

        AnsiString temp;


                temp.sprintf("0");
                KeyRedEdit->Text = temp;

                temp.sprintf("0");
                KeyGreenEdit->Text = temp;

                temp.sprintf("0");
                KeyBlueEdit->Text = temp;

                temp.sprintf("0");
                ColorRedEdit->Text = temp;

                temp.sprintf("0");
                ColorGreenEdit->Text = temp;

                temp.sprintf("0");
                ColorBlueEdit->Text = temp;

                temp.sprintf("0");
               FringRedEdit->Text = temp;

                temp.sprintf("0");
                FringGreenEdit->Text = temp;

                temp.sprintf("0");
                FringBlueEdit->Text = temp;

                fringingcheckbox->Checked=false;



                hfflocedit->Clear();

                fontscroll1->Image1->Picture=NULL;

        if(HFFFiles->ItemIndex < 0) DisableFontEdit();


}
//---------------------------------------------------------------------------


void __fastcall TForm1::coloreditClick(TObject * Sender)
{

        if(HFFFiles->ItemIndex <0)
        {
                MessageBox(Form1->Handle, "Select an HFF to edit", "Error", MB_OK);
                return;
        }
        //TODO: Add your source code here
}

void __fastcall TForm1::HFFFilesClick(TObject *Sender)
{
        if(HFFFiles->ItemIndex >= 0)
        {
                EnableFontEdit();
                AnsiString temp;
                HFFFile *hff = hffs[HFFFiles->ItemIndex];

                temp.sprintf("%i", hff->keyred);
                KeyRedEdit->Text = temp;

                temp.sprintf("%i", hff->keygreen);
                KeyGreenEdit->Text = temp;

                temp.sprintf("%i", hff->keyblue);
                KeyBlueEdit->Text = temp;

                temp.sprintf("%i", hff->colorred);
                ColorRedEdit->Text = temp;

                temp.sprintf("%i", hff->colorgreen);
                ColorGreenEdit->Text = temp;

                temp.sprintf("%i", hff->colorblue);
                ColorBlueEdit->Text = temp;

                 temp.sprintf("%i", hff->fringred);
                FringRedEdit->Text = temp;

                temp.sprintf("%i", hff->fringgreen);
                FringGreenEdit->Text = temp;

                temp.sprintf("%i", hff->fringblue);
                FringBlueEdit->Text = temp;

                if(hff->keyred != hff->fringred) fringingcheckbox->Checked=true;
                else fringingcheckbox->Checked=false;

               fontscroll1->Image1->Picture = hff->tpic;

                hfflocedit->Text = hff->full_path_name;


        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveAllHFFs1Click(TObject *Sender)
{
        for(int i=0; i<hffs.size(); i++)
        {
                HFFFiles->ItemIndex=i;
                SaveHFFClick(Sender);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::hfflocbutClick(TObject *Sender)
{
        if(DialogNewHFF->Execute())
        {
                needtosave=true;
                //fclose(hsfs[HSFFiles->ItemIndex]->file);
                //hsfs[HSFFiles->ItemIndex]->file = fopen(DialogHSFLoc->FileName.c_str(), "wb");
                hffs[HFFFiles->ItemIndex]->full_path_name = DialogNewHFF->FileName;
                hffs[HFFFiles->ItemIndex]->filename = ExtractFileName(DialogNewHFF->FileName);
                hfflocedit->Text = DialogNewHFF->FileName;
                int index = HFFFiles->ItemIndex;
                HFFFiles->Items->Delete(index);
                HFFFiles->Items->Insert(index, hffs[index]->filename);
                HFFFiles->ItemIndex=index;

        }
}
//---------------------------------------------------------------------------


HFFFile::SaveProj(FILE * fp)
{
        int temp;
        int bold, italic, underline, strike;

        bold = font->Style.Contains(fsBold);
        italic = font->Style.Contains(fsItalic);
        underline = font->Style.Contains(fsUnderline);
        strike = font->Style.Contains(fsStrikeOut);


        temp = font->Name.Length();
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(font->Name.c_str(), sizeof(char), temp, fp);
        temp = font->Size;
        fwrite(&temp, sizeof(int), 1, fp);
        fwrite(&bold, sizeof(int), 1, fp);
        fwrite(&italic, sizeof(int), 1, fp);
        fwrite(&underline, sizeof(int), 1, fp);
        fwrite(&strike, sizeof(int), 1, fp);
        fwrite(&keyred, sizeof(int), 1, fp);
        fwrite(&keygreen, sizeof(int), 1, fp);
        fwrite(&keyblue, sizeof(int), 1, fp);
        fwrite(&colorred, sizeof(int), 1, fp);
        fwrite(&colorgreen, sizeof(int), 1, fp);
        fwrite(&colorblue, sizeof(int), 1, fp);
        fwrite(&fringred, sizeof(int), 1, fp);
        fwrite(&fringgreen, sizeof(int), 1, fp);
        fwrite(&fringblue, sizeof(int), 1, fp);



        //TODO: Add your source code here
}

HFFFile::LoadProj(FILE * fp)
{
        int str_len, bold, italic, underline, strike, size;
        char buffer[512];
        AnsiString ansi_buffer;

        fread(&str_len, sizeof(int), 1, fp);
        fread(buffer, sizeof(char), str_len, fp);
        buffer[str_len]='\0';
        ansi_buffer.sprintf("%s", buffer);

        font = new TFont;
        font->Name = ansi_buffer;
        fread(&size, sizeof(int), 1, fp);
        fread(&bold, sizeof(int), 1, fp);
        fread(&italic, sizeof(int), 1, fp);
        fread(&underline, sizeof(int), 1, fp);
        fread(&strike, sizeof(int), 1, fp);

        font->Size = size;
        if(bold) font->Style = font->Style << fsBold;
        if(italic) font->Style = font->Style << fsItalic;
        if(underline) font->Style = font->Style << fsUnderline;
        if(strike) font->Style = font->Style << fsStrikeOut;

        fread(&keyred,  sizeof(int), 1, fp);
        fread(&keygreen, sizeof(int), 1, fp);
        fread(&keyblue, sizeof(int), 1, fp);
        fread(&colorred, sizeof(int), 1, fp);
        fread(&colorgreen, sizeof(int), 1, fp);
        fread(&colorblue, sizeof(int), 1, fp);
        fread(&fringred, sizeof(int), 1, fp);
        fread(&fringgreen, sizeof(int), 1, fp);
        fread(&fringblue, sizeof(int), 1, fp);

        tpic = new Graphics::TPicture;
        tbitmap = new Graphics::TBitmap;

        
        
        //TODO: Add your source code here
}




void __fastcall TForm1::backgroundcolorbutClick(TObject *Sender)
{
        DWORD temp;

        if(DialogBackGroundColor->Execute())
        {
                needtosave=true;
                temp = ColorToRGB(DialogBackGroundColor->Color);

                hffs[HFFFiles->ItemIndex]->keyblue= (((temp) >> 16) & 0xff);
                hffs[HFFFiles->ItemIndex]->keygreen= (((temp) >> 8) & 0xff);
                hffs[HFFFiles->ItemIndex]->keyred= ((temp) & 0xff);


                if(!fringingcheckbox->Checked)
                {
                        hffs[HFFFiles->ItemIndex]->fringblue= (((temp) >> 16) & 0xff);
                        hffs[HFFFiles->ItemIndex]->fringgreen= (((temp) >> 8) & 0xff);
                        hffs[HFFFiles->ItemIndex]->fringred= ((temp) & 0xff);
                }

                AnsiString temps;
                HFFFile *hff = hffs[HFFFiles->ItemIndex];

                temps.sprintf("%i", hff->keyred);
                KeyRedEdit->Text = temps;

                temps.sprintf("%i", hff->keygreen);
                KeyGreenEdit->Text = temps;

                temps.sprintf("%i", hff->keyblue);
                KeyBlueEdit->Text = temps;


                temps.sprintf("%i", hff->fringred);
                FringRedEdit->Text = temps;

                temps.sprintf("%i", hff->fringgreen);
                FringGreenEdit->Text = temps;

                temps.sprintf("%i", hff->fringblue);
                FringBlueEdit->Text = temps;
        }



}
//---------------------------------------------------------------------------

void __fastcall TForm1::foregroundcolorbutClick(TObject *Sender)
{
        DWORD temp;

        if(DialogBackGroundColor->Execute())
        {
                needtosave = true;
                temp = ColorToRGB(DialogBackGroundColor->Color);

                hffs[HFFFiles->ItemIndex]->colorblue= (((temp) >> 16) & 0xff);
                hffs[HFFFiles->ItemIndex]->colorgreen= (((temp) >> 8) & 0xff);
                hffs[HFFFiles->ItemIndex]->colorred= ((temp) & 0xff);

               

                AnsiString temps;
                HFFFile *hff = hffs[HFFFiles->ItemIndex];

                temps.sprintf("%i", hff->colorred);
                ColorRedEdit->Text = temps;

                temps.sprintf("%i", hff->colorgreen);
                ColorGreenEdit->Text = temps;

                temps.sprintf("%i", hff->colorblue);
                ColorBlueEdit->Text = temps;


        }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::OptionsClick(TObject *Sender)
{
        if(DialogOptions->ShowModal())
        {
                if(DialogOptions->saveproject)
                {
                        TimerAutoSave->Enabled = true;
                        TimerAutoSave->Interval = DialogOptions->autosavetime * 60 * 1000;
                }
                else TimerAutoSave->Enabled = false;
       }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::AutoSave(TObject *Sender)
{
        SaveGameClick(Sender);
        //TODO: Add your source code here
}
//---------------------------------------------------------------------------


TForm1::DisableFontEdit()
{
        KeyRedEdit->Enabled=false;
        KeyGreenEdit->Enabled=false;
        KeyBlueEdit->Enabled=false;
        ColorRedEdit->Enabled=false;
        ColorBlueEdit->Enabled=false;
        ColorGreenEdit->Enabled=false;
        FringRedEdit->Enabled=false;
        FringBlueEdit->Enabled=false;
        FringGreenEdit->Enabled=false;

        backgroundcolorbut->Enabled=false;
        foregroundcolorbut->Enabled=false;
        fringingcolorbut->Enabled = false;
        fringingcheckbox->Enabled = false;
        
        choosefontbut->Enabled=false;
        Button2->Enabled = false;

        hfflocedit->Enabled = false;
        hfflocbut->Enabled = false;

 //       AddFont1->Enabled = false;
        RemoveHFF1->Enabled=false;
        SaveHFF1->Enabled = false;

        //TODO: Add your source code here
}

TForm1::EnableFontEdit()
{
        KeyRedEdit->Enabled=true;
        KeyGreenEdit->Enabled=true;
        KeyBlueEdit->Enabled=true;
        ColorRedEdit->Enabled=true;
        ColorBlueEdit->Enabled=true;
        ColorGreenEdit->Enabled=true;

        backgroundcolorbut->Enabled=true;
        foregroundcolorbut->Enabled=true;

        choosefontbut->Enabled=true;
        Button2->Enabled = true;

        hfflocedit->Enabled = true;
        hfflocbut->Enabled = true;

        AddFont1->Enabled = true;
        RemoveHFF1->Enabled=true;
        SaveHFF1->Enabled = true;

        fringingcheckbox->Enabled=true;
        if(fringingcheckbox->Checked)
        {
                FringRedEdit->Enabled=true;
                FringBlueEdit->Enabled=true;
                FringGreenEdit->Enabled=true;
                fringingcolorbut->Enabled=true;
        }

        //TODO: Add your source code here
}
void __fastcall TForm1::onClose(TObject *Sender, TCloseAction &Action)
{
        ExitClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fringingcolorbutClick(TObject *Sender)
{
        if(DialogFringingColor->Execute())
        {
                needtosave=true;
                DWORD temp;

                temp = ColorToRGB(DialogFringingColor->Color);

                hffs[HFFFiles->ItemIndex]->fringblue= (((temp) >> 16) & 0xff);
                hffs[HFFFiles->ItemIndex]->fringgreen= (((temp) >> 8) & 0xff);
                hffs[HFFFiles->ItemIndex]->fringred= ((temp) & 0xff);


                AnsiString temps;
                HFFFile *hff = hffs[HFFFiles->ItemIndex];

                temps.sprintf("%i", hff->fringred);
                FringRedEdit->Text = temps;

                temps.sprintf("%i", hff->fringgreen);
                FringGreenEdit->Text = temps;

                temps.sprintf("%i", hff->fringblue);
                FringBlueEdit->Text = temps;
                

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fringcolorcheckOnClick(TObject *Sender)
{
        if(fringingcheckbox->Checked)
        {
                fringingcolorbut->Enabled=true;
                FringRedEdit->Enabled=true;
                FringGreenEdit->Enabled=true;
                FringBlueEdit->Enabled=true;
        }
        else
        {
                fringingcolorbut->Enabled=false;
                FringRedEdit->Enabled=false;
                FringGreenEdit->Enabled=false;
                FringBlueEdit->Enabled=false;

                if(HFFFiles->ItemIndex >= 0)
                {
                        HFFFile* temp = hffs[HFFFiles->ItemIndex];

                        temp->fringred = temp->keyred;
                        temp->fringblue = temp->keyblue;
                        temp->fringgreen = temp->keygreen;

                        AnsiString temps;

                        temps.sprintf("%i", temp->fringred);
                        FringRedEdit->Text = temps;

                        temps.sprintf("%i", temp->fringgreen);
                        FringGreenEdit->Text = temps;

                        temps.sprintf("%i", temp->fringblue);
                        FringBlueEdit->Text = temps;

                }



        }

}
//---------------------------------------------------------------------------


DispatchMessage(char* msg)
{
        AnsiString temp;

        temp.sprintf("%s", msg);

        MessageQue->Items->Add(temp);
        //TODO: Add your source code here
}

PNGChunk::~PNGChunk()
{
 //       delete[] data;
        //TODO: Add your source code here
}

HFFFile::~HFFFile()
{
  //      delete tbitmap;
   //     delete tpic;
  //      delete[] bits;
   //     delete font;

        
        //TODO: Add your source code here
}

HPTWav::~HPTWav()
{
       // delete[] data;
        //delete[] zlib_data;
        //delete[] fil_data;

        //TODO: Add your source code here
}

void __fastcall TForm1::fronttibutClick(TObject *Sender)
{
        AddImage->InitialDir = fronttileimageedit->Text;

        if(AddImage->Execute())
        {
                needtosave=true;

                levels[LevelsList->ItemIndex]->tileimage_layer1 = AddImage->FileName;
                fronttileimageedit->Text = AddImage->FileName;

                //Open File and Extract Number Tiles
                int imgwidth;
                char temp[255];
                PNG *pngtemp = new PNG;
                FILE *tempfile;

                tempfile = fopen(levels[LevelsList->ItemIndex]->tileimage_layer1.c_str(), "rb");


                pngtemp->LoadData(tempfile);
                imgwidth = pngtemp->GetPNGWidth();
                sprintf(temp, "%d", imgwidth/16);

                frontlayernumbertiles->Text = temp;

                levels[LevelsList->ItemIndex]->num_frontlayer_tiles = imgwidth/16;

                delete pngtemp;

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::backtibutClick(TObject *Sender)
{
        AddImage->InitialDir = fronttileimageedit->Text;

        if(AddImage->Execute())
        {
                needtosave=true;
                levels[LevelsList->ItemIndex]->tileimage_layer2 = AddImage->FileName;
                backtileimageedit->Text = AddImage->FileName;

                //Open File and Extract Number Tiles
                int imgwidth;
                char temp[255];
                PNG *pngtemp = new PNG;
                FILE *tempfile;

                tempfile = fopen(levels[LevelsList->ItemIndex]->tileimage_layer2.c_str(), "rb");

                pngtemp->LoadData(tempfile);
                imgwidth = pngtemp->GetPNGWidth();
                sprintf(temp, "%d", imgwidth/16);

                scrollinglayernumbertiles->Text = temp;

                levels[LevelsList->ItemIndex]->num_backlayer_tiles = imgwidth/16;

                delete pngtemp;

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mapdatabutClick(TObject *Sender)
{
        AddImage->InitialDir = mapdataedit->Text;

        if(DialogMapData->Execute())
        {
                needtosave=true;
                levels[LevelsList->ItemIndex]->map_data = DialogMapData->FileName;
                mapdataedit->Text = DialogMapData->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fronttdbutClick(TObject *Sender)
{
        AddImage->InitialDir = fronttiledataedit->Text;

        if(DialogTileData->Execute())
        {
                needtosave=true;
                levels[LevelsList->ItemIndex]->tiledata_layer1 = DialogTileData->FileName;
                fronttiledataedit->Text = DialogTileData->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::backtdbutClick(TObject *Sender)
{
        AddImage->InitialDir = backtiledataedit->Text;

         if(DialogTileData->Execute())
        {
                needtosave=true;
                levels[LevelsList->ItemIndex]->tiledata_layer2 = DialogTileData->FileName;
                backtiledataedit->Text = DialogTileData->FileName;
        }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::BuildProject1Click(TObject *Sender)
{
        SaveAllHGFSClick(Sender);
        SaveAllHFFs1Click(Sender);
        SaveAllHSFSClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CreateNewLevelClick(TObject *Sender)
{
        if(NewLevelDialog->Execute())
        {
                AnsiString ansibuffer;

                needtosave = true;
                Level* templevel;
                templevel = new Level;

    //            ansibuffer.sprintf("%s.hlf", NewLevelDialog->FileName.c_str());

                templevel->level_name = NewLevelDialog->FileName;//ansibuffer ;
                //leveloutputedit->Text = templevel->level_name;

          //      OutputDebugString("BLAH");
           //     OutputDebugString(templevel->level_name.c_str());

                LevelsList->Items->Add(ExtractFileName(templevel->level_name));

                levels.push_back(templevel);

        }
}
//---------------------------------------------------------------------------





void __fastcall TForm1::LevelsListClick(TObject *Sender)
{
        int index = LevelsList->ItemIndex;
        char temp[255];

        EnableLevels();

        mapdataedit->Text = levels[index]->map_data;
        fronttileimageedit->Text = levels[index]->tileimage_layer1;
        backtileimageedit->Text = levels[index]->tileimage_layer2;
        fronttiledataedit->Text = levels[index]->tiledata_layer1;
        backtiledataedit->Text = levels[index]->tiledata_layer2;
        leveloutputedit->Text = levels[index]->level_name;

        sprintf(temp, "%d", levels[index]->num_frontlayer_tiles);

        frontlayernumbertiles->Text = temp;

                
}
//---------------------------------------------------------------------------


TForm1::EnableLevels()
{
        mapdataedit->Enabled = true;
        fronttileimageedit->Enabled = true;
        backtileimageedit->Enabled = true;
        fronttiledataedit->Enabled = true;
        backtiledataedit->Enabled = true;
        leveloutputedit->Enabled = true;
        mapdatabut->Enabled = true;
        fronttibut->Enabled = true;
        backtibut->Enabled = true;
        fronttdbut->Enabled = true;
        backtdbut->Enabled = true;
        leveloutputbut->Enabled = true;
        //levelapplychanges->Enabled = true;

}

Level::Level()
{
        num_frontlayer_tiles = 0;
        num_backlayer_tiles = 0;
        
        //TODO: Add your source code here
}

Level::WriteHLF()
{
        AnsiString filename;
        FILE* output;
        FILE* map_script;
        char temps[512];

//        filename = Form1->leveloutputedit->Text;
 //       filename += ".hlf"
        filename = level_name.c_str();
        filename += ".hlf";
        output = fopen(filename.c_str(), "wb");
        if(output == NULL)
        {
                sprintf(temps, "Error Building %s: Unable to open %s", ExtractFileName(level_name).c_str(), filename);
                DispatchMessage(temps);
                return 0;
        }

        map_script = fopen(map_data.c_str(), "r");
        if(map_script == NULL)
        {
                sprintf(temps, "Error Building %s: Unable to open %s", ExtractFileName(level_name).c_str(), map_data.c_str());
                DispatchMessage(temps);
                return 0;
        }

        int width, height;
	unsigned char *mapdata;

	fscanf(map_script, "%i %i", &width, &height);

	//load in tile matrix data
	mapdata=new unsigned char[width*height];
	for(int i=0; i<(height*width); i++)
	{
		int temp;
		if(fscanf(map_script, "%d", &temp))
                {        char temp2[266];
                        sprintf(temp2, "%d", i);
                        OutputDebugString(temp2);
                        mapdata[i] = (unsigned char) temp;
                        }
                else
                        ;//nothing;


	}

	//load in image data
	//png.load_image_data(tile_image);

//	png.write_file(output);
	
	char *HLF="HLF";
	int version = 1;

	fwrite(HLF, sizeof(char), 3, output);
	fwrite(&version, sizeof(int), 1, output);
	fwrite(&width, sizeof(int), 1, output);
	fwrite(&height, sizeof(int), 1, output);
	fwrite(mapdata, sizeof(unsigned char), width*height, output);




	fclose(map_script);
	//fclose(tile_image);
	fclose(output);


        //TODO: Add your source code here
}
void __fastcall TForm1::SaveLevelClick(TObject *Sender)
{
        if(LevelsList->ItemIndex > -1)
        {
                levels[LevelsList->ItemIndex]->WriteHLF();
                levels[LevelsList->ItemIndex]->WriteLayer1HTF();
                levels[LevelsList->ItemIndex]->WriteLayer2HTF();
       }
}
//---------------------------------------------------------------------------


Level::WriteLayer1HTF()
{
       	FILE *tile_script;
	FILE *tile_image;
	FILE *output;
	char file_ext[4]="";
        AnsiString output_filename;
//    	sprintf(output_filename, "%s", level_name.c_str());
        output_filename = level_name;
        output_filename += "f.htf";
        if(tiledata_layer1.IsEmpty())
                return 0;

	tile_script=fopen(tiledata_layer1.c_str(), "r");
	output=fopen(output_filename.c_str(), "wb");




		HTFPng png;
                png.width = 16;
                png.height = 16;
		//load in image data
		png.load_image_data(tile_script);


		if(fscanf(tile_script, " %i %i", &(png.matrix_width), &(png.matrix_height)) == EOF)
                        MessageBox(NULL,"error","error",MB_OK);;

		//load in tile matrix data
		png.matrix_keys=new unsigned int[png.matrix_height*png.matrix_width];
		for(int i=0; i<(png.matrix_height*png.matrix_width); i++)
		{
			int temp;
			fscanf(tile_script, " %i", &temp);
			if(temp < 0) temp =0;

			png.matrix_keys[i] = (unsigned int) temp;

		}

       //		png.CombineImage();
	//	png.DecompressImage();
       //		png.GenerateKeys();
       //		png.FlattenTiles();
		png.RemoveDuplicates();
		png.RemoveHDuplicates();

		png.GenerateOutputImage();
		png.CompressImage();
		png.GenerateNewEntrys();
		png.CreateTiles();
		png.write_file(output);




	fclose(tile_script);
//	fclose(tile_image);
	fclose(output);

}


Level::WriteLayer2HTF()
{
       	FILE *tile_script;
	FILE *tile_image;
	FILE *output;
	char file_ext[4]="";
        AnsiString output_filename;
//    	sprintf(output_filename, "%s", level_name.c_str());
        output_filename = level_name;
        output_filename += "b.htf";
        
        if(tiledata_layer2.IsEmpty())
                return 0;

	tile_script=fopen(tiledata_layer2.c_str(), "r");
	output=fopen(output_filename.c_str(), "wb");




		HTFPng png;
                png.width = 16;
                png.height = 16;
		//load in image data
		png.load_image_data(tile_script);


		fscanf(tile_script, "%i %i ", &png.matrix_width, &png.matrix_height);

		//load in tile matrix data
		png.matrix_keys=new unsigned int[png.matrix_height*png.matrix_width];
		for(int i=0; i<(png.matrix_height*png.matrix_width); i++)
		{
			int temp;
			fscanf(tile_script, "%i", &temp);
			if(temp < 0) temp =0;

			png.matrix_keys[i] = (unsigned int) temp;

		}

       //		png.CombineImage();
	//	png.DecompressImage();
       //		png.GenerateKeys();
       //		png.FlattenTiles();
		png.RemoveDuplicates();
		png.RemoveHDuplicates();

		png.GenerateOutputImage();
		png.CompressImage();
		png.GenerateNewEntrys();
		png.CreateTiles();
		png.write_file(output);




	fclose(tile_script);
	fclose(tile_image);
	fclose(output);


}














