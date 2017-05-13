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
    coor coordinate;

    fieldData(mapEditor* mE, coor coordinate)
    : myEditor(mE), coordinate(coordinate), origo(coordinate*mapEditor::FIELD_WIDTH+mapEditor::MAP_OFFSET)
    {
        mE->widgets.push_back(new lButton([this](){this->clicked();},origo,mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH,"",0,false));
    }

    void clicked()
    {
        if (myEditor->moveULC)
        {
            myEditor->uLC=coordinate;
            myEditor->moveULC=false;
        }
        else if (myEditor->moveDRC)
        {
            myEditor->dRC=coordinate;
            myEditor->moveDRC=false;
        }
        else if (myEditor->currPart=="delete")
            clearPart();
        else
        {
            addPart(myEditor->currPart, myEditor->currOwner);
        }
    }

    void addPart(string partName, int pplayer)
    {
        if (!hasPart(partName))
        {
            parts.push_back(part(partName,origo,myEditor));
            player=pplayer;
        }
    }

    bool hasPart(string partName)
    {
        for (part p:parts)
            if (p.name==partName)
                return true;
        return false;
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
        if (!(coordinate>=myEditor->uLC && coordinate<=myEditor->dRC)) //if not in selected area
        {
            drawLine(origo-makeCoor(mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2,origo+makeCoor(mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2,100,100,100);
            drawLine(origo-makeCoor(-mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2,origo+makeCoor(-mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2,100,100,100);
        }
        //szebb, de lassú:
        //darkening(2,origo-makeCoor(mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2,origo+makeCoor(mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH)/2);
    }
};

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
        if (fieldObject::EVERY_OBJECT[i]!=fieldObject::BARRACK&&fieldObject::EVERY_OBJECT[i]!=fieldObject::STRONGHOLD)
            widgets.push_back(new lButton([this,i](){this->currPart=fieldObject::EVERY_OBJECT[i];this->currOwner=-1;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*(i+objStart)+cutDist*cutNum),wid,hei,fieldObject::EVERY_OBJECT[i],fSize));
        else
            widgets.push_back(new lButton([this,i](){this->currPart=fieldObject::EVERY_OBJECT[i];},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*(i+objStart)+cutDist*cutNum),wid,hei,fieldObject::EVERY_OBJECT[i],fSize));
    //cutNum++;
    widgets.push_back(new lButton([this](){this->currPart="delete";},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*12+cutDist*cutNum),wid,hei,"Delete",fSize));

    cutNum++;
    widgets.push_back(new lButton([this](){this->moveULC=true;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*13+cutDist*cutNum),wid,hei,"ULC",fSize));
    widgets.push_back(new lButton([this](){this->moveDRC=true;},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*14+cutDist*cutNum),wid,hei,"DRC",fSize));

    cutNum++;
    widgets.push_back(new lButton([this](){this->symmetrieOrdered();},makeCoor(WINDOW_X-oDistFromEdgeX,oDistFromEdgeY+dist*15+cutDist*cutNum),wid,hei,"Symmetrie",fSize));

    draw();
    generateFields();
}

void mapEditor::symmetrieOrdered()
{
    double xAxis=(double)(dRC.X-uLC.X+1)/2.0+uLC.X;
    int xStart=uLC.X;
    int xEnd=(int)xAxis;
    int yStart=uLC.Y;
    int yEnd=dRC.Y+1;
    cout<<"axis: "<<xAxis<<" xStart: "<<xStart<<" yStart: "<<yStart<<" xEnd: "<< xEnd<<" yEnd: "<<yEnd<<endl;
    for (int y=yStart;y<yEnd;y++)
    {
        for (int x=xStart;x<xEnd;x++)
        {
            currOwner=fields[y][x]->player;
            if (currOwner==1)
                currOwner=0;
            else if (currOwner==0)
                currOwner=1;
            for (part p:fields[y][x]->parts)
                if (p.name==fieldObject::EAST_ROAD)
                    fields[y][xAxis*2-x-1]->addPart(fieldObject::WEST_ROAD,currOwner);
                else if (p.name==fieldObject::WEST_ROAD)
                    fields[y][xAxis*2-x-1]->addPart(fieldObject::EAST_ROAD,currOwner);
                else
                    fields[y][xAxis*2-x-1]->addPart(p.name,currOwner);
        }
    }
}

void mapEditor::draw()
{
    screen::draw();
}

void mapEditor::generateFields()
{
    for (int i=0;i<MAX_HEIGHT;i++)
    {
        vector<fieldData*> newRow;
        for (int j=0;j<MAX_WIDTH;j++)
        {
            fieldData* newField=new fieldData(this,makeCoor(j,i));
            newRow.push_back(newField);
        }
        fields.push_back(newRow);
    }
}

void mapEditor::drawMarkers()
{
    //object marker
    int obIndex=find(fieldObject::EVERY_OBJECT.begin(),fieldObject::EVERY_OBJECT.end(),currPart)-fieldObject::EVERY_OBJECT.begin();
    drawLine(makeCoor(WINDOW_X-oDistFromEdgeX-wid*3.0/4.0,obIndex*dist+obStart),
             makeCoor(WINDOW_X-oDistFromEdgeX-wid*2.0/4.0,obIndex*dist+obStart));
    //player marker
    drawLine(makeCoor(WINDOW_X-oDistFromEdgeX-wid*3.0/4.0,(currOwner+1)*dist+playerStart),
             makeCoor(WINDOW_X-oDistFromEdgeX-wid*2.0/4.0,(currOwner+1)*dist+playerStart));
    //border markers
    coor uLCorner=(uLC-0.5)*FIELD_WIDTH+MAP_OFFSET;
    coor dRCorner=(dRC+0.5)*FIELD_WIDTH+MAP_OFFSET;
    int length=10;
    int width=2;
    int r=238;
    int g=238;
    int b=0;
    drawFatLine(uLCorner,uLCorner+makeCoor(0,length),width,r,g,b);
    drawFatLine(uLCorner,uLCorner+makeCoor(length,0),width,r,g,b);
    drawFatLine(dRCorner,dRCorner+makeCoor(0,-length),width,r,g,b);
    drawFatLine(dRCorner,dRCorner+makeCoor(-length,0),width,r,g,b);
    //symmetrie axis
    double xAxis=(double)(dRC.X-uLC.X+1)/2.0/*+uLC.X*/;
    drawFatLine(uLCorner+makeCoor(FIELD_WIDTH*(xAxis),0),dRCorner-makeCoor(FIELD_WIDTH*(xAxis),0),width,r,g,b);
}

void mapEditor::mayWarn()
{
    bool shallWarn=false;
    if (currOwner==-1) //no owner
        if (currPart==fieldObject::BARRACK)
            shallWarn=true;
        else shallWarn=false;
    else
        if (currPart!=fieldObject::BARRACK && currPart!=fieldObject::STRONGHOLD)
            shallWarn=true;
    if (!(uLC<=dRC))
        shallWarn=true;
    if (shallWarn)
        for (int i=0;i<5;i++)
            drawRectangle(makeCoor(i,i),makeCoor(WINDOW_X-i,WINDOW_Y-i),false,255,0,0);
}

void mapEditor::onTick()
{
    clearScreen();
    for (vector<fieldData*> fRow:fields)
        for (fieldData* f:fRow)
            f->draw();
    mayWarn();
    screen::onTick();
    drawMarkers();
}

void mapEditor::save(string mapName) //no overwrite test
{
    string fileName="maps/";
    fileName+=mapName;
    fileName+=".txt";
    ofstream file(fileName);
    int width=dRC.X-uLC.X+1;
    int height=dRC.Y-uLC.Y+1;
    file<<width<<" "<<height<<endl;
    for (int i=uLC.X;i<=dRC.X;i++)
    {
        for (int j=uLC.Y;j<=dRC.Y;j++)
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
    //if (generateDescFile)
    {
        ofstream descFile("maps/descriptions/"+mapName+".txt");
        descFile<<mapName+"'s description comes here.";
        descFile.close();
    }
}
