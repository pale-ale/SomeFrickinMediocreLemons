#include "TextBox.h"
TextBox::TextBox(UISystem* ui, sf::Vector2f size, unsigned int fontsize, string content, bool autoresize, bool texthover):UIElement(ui), 
fontsize{fontsize}, sizetextbox{size}, content{content}, autoresize{autoresize}, texthover{texthover} {
    this->font->loadFromFile(Settings::validFontPath);
    this->uicontent.setFont(*font);
    this->autoresize = autoresize;
    this->size = size;
    this->content = content;
    updatetextboxShape();
    cout << "Position:" << hitbox.size() << endl;
    updateContent();
}

bool TextBox::updateContent(){
    list<string> wordlist;
    //fill the wordlist with content 
	
    istringstream iss(content);
    string token;
    while(getline(iss, token, ' ')){
        wordlist.push_back(token);
    }
    iss.clear();
    auto iterator = wordlist.begin();
    sf::Text uicontentboundaries = sf::Text();
    uicontentboundaries.setFont(*font);
    uicontentboundaries.setScale(uicontent.getScale());
    uicontent.setString("");
    //foreach element in wordlist check if width is to large
    //if the autoresize is off show hovering text instead
    if(!autoresize){
        uicontent.setCharacterSize(fontsize);
    }
    uicontentboundaries.setCharacterSize(this->fontsize);
    while(iterator != wordlist.end()){
        uicontentboundaries.setString(this->uicontent.getString());
        uicontentboundaries.setString(uicontentboundaries.getString()+*iterator + " ");
        if(uicontentboundaries.getGlobalBounds().width > this->size.x){
            this->uicontent.setString(this->uicontent.getString() + "\n" + *iterator + " ");
        }
        else{
            this->uicontent.setString(this->uicontent.getString() + *iterator + " ");
        }
        iterator++;
        //if the uicontent does not fit to y size the need to resize the character size and restart the procedure
        if(this->uicontent.getGlobalBounds().height > this->size.y || this->uicontent.getGlobalBounds().width > this->size.x){
            if(this->uicontent.getCharacterSize()!=0 && autoresize){
            this->uicontent.setCharacterSize(this->uicontent.getCharacterSize()-1);
            uicontentboundaries.setCharacterSize(this->uicontent.getCharacterSize());
            //begin the procedure again, because character size has changed
            iterator = wordlist.begin();
            uicontent.setString("");
            uicontentboundaries.setString("");
            }
            else{
                return false;
            }
        }
    }
    return true;
}

void TextBox::setHitbox(const vector<sf::Vector2f> & hitbox){
    this->hitbox = hitbox;
}

void TextBox::updatetextboxShape(){
    textboxShape.setPointCount(hitbox.size());
    textboxShape.setFillColor(this->backgroundColor);
    auto& hb = getHitboxPolygonGlobal();
    for (int i = 0; i < hitbox.size(); i++)
    {
        textboxShape.setPoint(i, hb[i]);
    }
}
//this is for hovering text later if it does not fit to textbox
void TextBox::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addEventListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

bool TextBox::setContent(string content){
    this->content=content;
    return updateContent();
}

bool TextBox::setCharacterSize(unsigned int fontsize){
    this->fontsize = fontsize;
    this->uicontent.setCharacterSize(fontsize);
    return updateContent();
}

bool TextBox::setSize(sf::Vector2f size){
    this->size = size;
    updatetextboxShape();
    return updateContent();
}

void TextBox::setColor(sf::Color color){
    this->backgroundColor = color;
}

void TextBox::setPosition(const sf::Vector2f &newPosition){
    UIElement::setPosition(newPosition);
    uicontent.setPosition(newPosition);
    textboxShape.setPosition(newPosition);
}

void TextBox::setRotation(const float &newRotation){
    UIElement::setRotation(newRotation);
    uicontent.setRotation(newRotation);
    textboxShape.setRotation(newRotation);
}

void TextBox::setScale(float xScale, float yScale){
    UIElement::setScale(xScale, yScale);
    uicontent.setScale(xScale, yScale);
    textboxShape.setScale(xScale, yScale);
}

//will be implemented later
bool TextBox::OnBeginMouseover(){
    return true;
}

bool TextBox::OnEndMouseover(){
    return true;
}
