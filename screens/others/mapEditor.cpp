#include "mapEditor.h"

const coor mapEditor::MAP_OFFSET={50,50};

struct part
{
    string name;
    Picture pic;

    part(string name, coor origo, mapEditor* myEd)
    : name(name)
    {
        if (myEd->currOwner>-1)
            pic.addNewPic("pics/editor/player"+numToString(myEd->currOwner+1)+"/"+name+".kep",origo);
        else
            pic.addNewPic("pics/editor/"+name+".kep",origo);
        pic.setScaleX((double)mapEditor::FIELD_WIDTH/(double)pic.NORMAL_WIDTH);
        pic.setScaleY((double)mapEditor::FIELD_WIDTH/(double)pic.NORMAL_HEIGHT);
    }

    void draw()
    {
        pic.draw();
    }
};

struct fieldData
{
    int player=-1;
    vector<part> parts;
    mapEditor* myEditor;
    coor origo;

    fieldData(mapEditor* mE, coor origo)
    : myEditor(mE), origo(origo)
    {
        mE->widgets.push_back(new lButton([this](){this->addPart();},origo,mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH,"",0,false));
    }

    void addPart()
    {
        if (myEditor->currPart=="delete")
            clearPart();
        else
        {
            parts.push_back(part(myEditor->currPart,origo,myEditor));
            player=myEditor->currOwner;
        }
    }

    void clearPart()
    {
        parts.clear();
    }

    void draw()
    {
        for (part p:parts)
        {
            p.draw();
        }
    }
};
vector<vector<fieldData*>> fields;

mapEditor::mapEditor()
{
    widgets.push_back(new lButton([this](){newSub=screen::SAVE_MAP;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+cutDist*cutNum),wid,hei,"Save",fSize));

    cutNum++;
    playerStart=oDistFromEdgeY+dist+cutDist*cutNum;
    widgets.push_back(new lButton([this](){this->currOwner=-1;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist+cutDist*cutNum),wid,hei,"--",fSize));
    widgets.push_back(new lButton([this](){this->currOwner=0;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*2+cutDist*cutNum),wid,hei,"P 1",fSize));
    widgets.push_back(new lButton([this](){this->currOwner=1;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*3+cutDist*cutNum),wid,hei,"P 2",fSize));

    cutNum++;
    int objStart=widgets.size();
    obStart=oDistFromEdgeY+dist*(objStart)+cutDist*cutNum;
    for (int i=0;i<fieldObject::EVERY_OBJECT.size();i++)
        widgets.push_back(new lButton([this,i](){this->currPart=fieldObject::EVERY_OBJECT[i];},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*(i+objStart)+cutDist*cutNum),wid,hei,fieldObject::EVERY_OBJECT[i],fSize));

    cutNum++;
    widgets.push_back(new lButton([this](){this->currPart="delete";},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*12+cutDist*cutNum),wid,hei,"Delete",fSize));

    draw();
    generateFields();
}

void mapEditor::draw()
{
    //addTitle("Editor");
}

void mapEditor::generateFields()
{
    for (int i=0;i<MAX_HEIGHT;i++)
    {
        vector<fieldData*> newRow;
        for (int j=0;j<MAX_WIDTH;j++)
        {
            fieldData* newField=new fieldData(this,makeCoor(j,i)*FIELD_WIDTH+MAP_OFFSET);
            newRow.push_back(newField);
        }
        fields.push_back(newRow);
    }
}

void mapEditor::drawMarkers()
{
    int obIndex=find(fieldObject::EVERY_OBJECT.begin(),fieldObject::EVERY_OBJECT.end(),currPart)-fieldObject::EVERY_OBJECT.begin();
    drawLine(makeCoor(WINDOW_X-oDistFromEdgeX-wid*3.0/4.0,obIndex*dist+obStart),
             makeCoor(WINDOW_X-oDistFromEdgeX-wid*2.0/4.0,obIndex*dist+obStart));

    drawLine(makeCoor(WINDOW_X-oDistFromEdgeX-wid*3.0/4.0,(currOwner+1)*dist+playerStart),
             makeCoor(WINDOW_X-oDistFromEdgeX-wid*2.0/4.0,(currOwner+1)*dist+playerStart));
}

void mapEditor::onTick()
{
    clearScreen();
    for (vector<fieldData*> fRow:fields)
        for (fieldData* f:fRow)
            f->draw();
    drawMarkers();
    screen::onTick();
}

void mapEditor::save(string mapName) //no overwrite test
{
    string fileName="maps/";
    fileName+=mapName;
    fileName+=".txt";
    cout<<fileName;
    ofstream file(fileName);
    file<<MAX_WIDTH<<" "<<MAX_HEIGHT<<endl;
    for (int i=0;i<MAX_WIDTH;i++)
    {
        for (int j=0;j<MAX_HEIGHT;j++)
        {
            fieldData* currField=fields[j][i];
            file<<currField->player<<" "<<currField->parts.size();
            for (int k=0;k<currField->parts.size();k++)
            {
                file<<currField->parts[k].name<<";";
            }
            file<<"\n";
        }
    }
    file.close();
    ofstream mapList("maps/mapList.txt",ofstream::app);
    mapList<<mapName<<endl;
    mapList.close();
}
