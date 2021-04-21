#include "TextBox.h"
//wip will modify on Saturday please do not touch until then
TextBox::TextBox(UISystem* ui, sf::Vector2f size, string content="", bool autoresize = true):UIElement(ui){
    this->autoresize = autoresize;
    this->size = size;
    this->content = content;
    UpdateContent();
}

bool TextBox::UpdateContent(){
    unsigned int character = 0;
    list<string> wordlist;
    auto iterator = wordlist.begin();
       //fill the wordlist with content
    while(character < this->content.length()){

    }
    sf::Text uicontentboundaries = sf::Text();
    //clear current Text in ui
    uicontent.setString("");
    //foreach element in wordlist check if width is to large
    //needs check for autoresize later on to apply different character size
    //if the autoresize is off show hovering text instead
    while(iterator != wordlist.end()){
        uicontentboundaries.setString(this->uicontent.getString());
        uicontentboundaries.setString(uicontentboundaries.getString()+*iterator);
        if(uicontentboundaries.getGlobalBounds().width > this->size.x){
            this->uicontent.setString(this->uicontent.getString() + "\n" + *iterator);
        }
        else{
            uicontentboundaries.setString(this->uicontent.getString() + *iterator);
        }
        if(this->uicontent.getGlobalBounds().height > this->size.y || this->uicontent.getGlobalBounds().width > this->size.x){
            return false;
        }
    }
    return true;
}

//this is for hovering text later if it does not fit to textbox
void TextBox::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addEventListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

bool TextBox::ChangeContent(char* content){
    this->content=content;
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

bool TextBox::ChangeCharacterSize(unsigned int size){
    this->uicontent.setCharacterSize(size);
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}
