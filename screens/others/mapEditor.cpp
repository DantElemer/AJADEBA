#include "mapEditor.h"

const coor mapEditor::MAP_OFFSET={50,50};

struct fieldData
{
    int player=-1;
    vector<string> parts;
    mapEditor* myEditor;

    fieldData(mapEditor* mE, coor origo)
    : myEditor(mE)
    {
        mE->widgets.push_back(new lButton([this](){this->addPart("ham");},origo,mapEditor::FIELD_WIDTH,mapEditor::FIELD_WIDTH));
    }

    void addPart(string part)
    {
        parts.push_back(myEditor->currPart);
        player=myEditor->currOwner;
    }

    void clearPart()
    {

    }
};
vector<vector<fieldData*>> fields;

mapEditor::mapEditor()
{
    int dist=40;
    widgets.push_back(new lButton([this](){this->save();},makeCoor(WINDOW_X-50,50),60,30,"Save",20));

    widgets.push_back(new lButton([this](){this->currOwner=0;},makeCoor(WINDOW_X-50,50+dist),60,30,"P 1",20));
    widgets.push_back(new lButton([this](){this->currOwner=1;},makeCoor(WINDOW_X-50,50+dist*2),60,30,"P 2",20));
    widgets.push_back(new lButton([this](){this->currOwner=-1;},makeCoor(WINDOW_X-50,50+dist*3),60,30,"--",20));

    widgets.push_back(new lButton([this](){this->currPart=fieldObject::BARRACK;},makeCoor(WINDOW_X-50,50+dist*4),60,30,"Barack",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::STRONGHOLD;},makeCoor(WINDOW_X-50,50+dist*5),60,30,"Strong",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::NORTH_ROAD;},makeCoor(WINDOW_X-50,50+dist*6),60,30,"N road",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::SOUTH_ROAD;},makeCoor(WINDOW_X-50,50+dist*7),60,30,"S road",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::EAST_ROAD;},makeCoor(WINDOW_X-50,50+dist*8),60,30,"E road",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::WEST_ROAD;},makeCoor(WINDOW_X-50,50+dist*9),60,30,"W road",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::VILLAGE;},makeCoor(WINDOW_X-50,50+dist*10),60,30,"Vill",20));
    widgets.push_back(new lButton([this](){this->currPart=fieldObject::MOUNTAIN;},makeCoor(WINDOW_X-50,50+dist*11),60,30,"Mount",20));
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

void mapEditor::save()
{
    string fileName="maps/editorTest.txt";
    ofstream file(fileName);
    file<<MAX_WIDTH<<" "<<MAX_HEIGHT<<endl;
    for (int i=0;i<MAX_HEIGHT;i++)
    {
        for (int j=0;j<MAX_WIDTH;j++)
        {
            fieldData* currField=fields[i][j];
            file<<currField->player<<" "<<currField->parts.size();
            for (int k=0;k<currField->parts.size();k++)
            {
                file<<currField->parts[k]<<";";
            }
            file<<"\n";
        }
    }
    //fclose(file);
}
