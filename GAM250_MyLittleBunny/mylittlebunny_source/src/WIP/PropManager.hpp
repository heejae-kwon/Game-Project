/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      PropManager.hpp
Purpose:        Handles the creation, destruction of Props. It also manages the correspondance table between props and their id name.
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props/Props.hh>

#include <string>
#include <list>

namespace BE
{
    //!  PropManager class. 
    /*!
     PropManager is in charge of handing out the props to the actors.
     If an actor wishes to use a prop it need to request it from the PropManager.
     All props need to be registered with the PropManager to be useable by actors.
    */
    class PropManager
    {
        // All type redefinitions should be at the start of a class
    public:
        using propNamePair = std::pair<std::string, Prop::BaseProp*>;
        using propNamePairList = std::vector<propNamePair*>;
    protected:
        using PropManagerSmartPtr = std::unique_ptr<PropManager>;
        using PropSmartPtr = std::unique_ptr<Prop::BaseProp>;
    public:
        using PropVec = std::vector<PropSmartPtr>;

    public:
        static PropManager*  instance()  //!< Returns an instance of the class
        {
            static PropManagerSmartPtr instance(new PropManager());
            return instance.get();
        }
        ~PropManager() = default;

        Prop::BaseProp*     createProp(std::string fileName_, Prop::Type propType_, std::string id_ = "NO_VALUE");
        Prop::BaseProp*     createPropFromFile(std::string fileName_, Json::Value& data_);
        propNamePair*       lookupValue(std::string id_);
        propNamePairList&   getCorresTable();
        bool                isFileLoaded(std::string filename_);
        void                addEntry(std::string id_, Prop::BaseProp* prop_);
        void                updateEntry(Prop::BaseProp* prop_);
        void                removeEntry(Prop::BaseProp* entry_);
        void                deleteEntry(Prop::BaseProp* entry_);

        std::vector<BE::Prop::BaseProp*>&            getProps();
    protected:
        //
    private:
        PropManager() = default;
        void    updateOrder();

    public:
        propNamePairList    _propCorrespondanceTable;
    protected:
        //
    private:
        PropVec _propVec;  /*!< The vector container that stores the unique pointers to all active props in our game */
        std::vector<Prop::BaseProp*> _ordererPropVec;
    };
}
