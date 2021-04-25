#include "TextBox.h"
TextBox::TextBox(UISystem* ui, sf::Vector2f size, unsigned int fontsize, string content, bool autoresize):UIElement(ui), 
fontsize{fontsize}, size{size}, content{content}, autoresize{autoresize} {
    this->font->loadFromFile(Settings::validFontPath);
    this->uicontent.setFont(*font);
    this->autoresize = autoresize;
    this->size = size;
    this->content = content;
    UpdateContent();
}

bool TextBox::UpdateContent(){
    list<string> wordlist;
    //fill the wordlist with content
    istringstream iss(content);
    string token;
    while(getline(iss, token, ' ')){
        wordlist.push_back(token);
        cout<< "token is " + token<< endl;
    }
    iss.clear();
    auto iterator = wordlist.begin();
    cout << "wordlist is " << wordlist.size() << endl;;
    sf::Text uicontentboundaries = sf::Text();
    uicontentboundaries.setFont(*font);
    uicontentboundaries.setScale(uicontent.getScale());
    uicontent.setString("");
    //foreach element in wordlist check if width is to large
    //if the autoresize is off show hovering text instead
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

//this is for hovering text later if it does not fit to textbox
void TextBox::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addEventListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

bool TextBox::changeContent(string content){
    this->content=content;
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

bool TextBox::changeCharacterSize(unsigned int fontsize){
    this->uicontent.setCharacterSize(fontsize);
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

bool TextBox::changeSize(sf::Vector2f size){
    this->size = size;
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

void TextBox::setPosition(const sf::Vector2f &newPosition){
    UIElement::setPosition(newPosition);
    uicontent.setPosition(newPosition);
}

void TextBox::setRotation(const float &newRotation){
    UIElement::setRotation(newRotation);
    uicontent.setRotation(newRotation);
}

void TextBox::setScale(float xScale, float yScale){
    UIElement::setScale(xScale, yScale);
    uicontent.setScale(xScale, yScale);
}

//will be implemented later
bool TextBox::OnBeginMouseover(){
    return true;
}

bool TextBox::OnEndMouseover(){
    return true;
}
