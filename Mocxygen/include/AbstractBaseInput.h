/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef _BASE_INPUT_H_
#define _BASE_INPUT_H_

#include <string>
#include "AbstractSerializable.h"
#include "Json.h"
#include "AbstractBaseOutput.h"
#include "Requester.h"
#include "Pageable.h"

namespace Mocxygen {
    class AbstractBaseInput : public Cmarshal::Json::AbstractSerializable {
    public:
        AbstractBaseInput() = default;

        virtual ~AbstractBaseInput() = default;

        virtual std::string ToString() const = 0;

        virtual std::string Name() const = 0;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;
        
        REGISTER_GETTER_INCLUDING_BASE_START(AbstractSerializable)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractSerializable)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T>
    class AbstractApiInput : public AbstractBaseInput {
    public:
        AbstractApiInput() = default;

        virtual ~AbstractApiInput() = default;

        web::json::value &Serialize() override {
            m_serializedValue = Cmarshal::Json::ToJson<T>(reinterpret_cast<const T *> (this));
            return m_serializedValue;
        }

        void Deserialize(const web::json::value &jvalue) override {
            Cmarshal::Json::FromJson<T>(reinterpret_cast<T *> (this), jvalue);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractBaseInput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractBaseInput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T>
    class AbstractApiGetInput : public AbstractApiInput<T> {
    public:
        AbstractApiGetInput() = default;

        virtual ~AbstractApiGetInput() = default;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiInput<T>)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiInput<T>)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T>
    class AbstractApiGetEntityInput : public AbstractApiGetInput<T> {
    public:
        AbstractApiGetEntityInput() = default;

        virtual ~AbstractApiGetEntityInput() = default;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;

        const boost::optional<long> & GetId() const {
            return m_Id;
        }

        void SetId(boost::optional<long> & Id) {
            AbstractApiGetEntityInput::m_Id = Id;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiGetInput<T>)
        GETTER(AbstractApiGetEntityInput<T>, const boost::optional<long>& , "id", &AbstractApiGetEntityInput<T>::GetId)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiGetInput<T>)
        SETTER(AbstractApiGetEntityInput<T>, boost::optional<long>& , "id", &AbstractApiGetEntityInput<T>::SetId)
        REGISTER_SETTER_INCLUDING_BASE_END

    protected:
        boost::optional<long> m_Id;
    };

    template<class T>
    class AbstractApiGetEntityListInput : public AbstractBaseInput {
    public:
        AbstractApiGetEntityListInput() = default;

        virtual ~AbstractApiGetEntityListInput() = default;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;

        web::json::value &Serialize() override {
            m_serializedValue = Cmarshal::Json::ToJson<T>(reinterpret_cast<const T *> (this));
            return m_serializedValue;
        }

        void Deserialize(const web::json::value &jvalue) override {
            Cmarshal::Json::FromJson<T>(reinterpret_cast<T *> (this), jvalue);
        }

        const boost::optional<Pageable> &GetPageable() const {
            return m_pageable;
        }
        void SetPageable(boost::optional<Pageable> &pageable) {
            m_pageable = pageable;
        }


        const boost::optional<std::vector<long>> &GetIds() const {
            return ids;
        }

        void SetIds(boost::optional<std::vector<long>> &ids) {
            AbstractApiGetEntityListInput::ids = ids;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractBaseInput)
        GETTER(AbstractApiGetEntityListInput<T>, const boost::optional<Pageable>&, "pageable", &AbstractApiGetEntityListInput<T>::GetPageable),
        GETTER(AbstractApiGetEntityListInput<T>, const boost::optional<std::vector<long>> &, "ids", &AbstractApiGetEntityListInput<T>::GetIds)

        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractBaseInput)
        SETTER(AbstractApiGetEntityListInput<T>, boost::optional<Pageable>&, "pageable", &AbstractApiGetEntityListInput<T>::SetPageable),
        SETTER(AbstractApiGetEntityListInput<T>, boost::optional<std::vector<long>> &, "ids", &AbstractApiGetEntityListInput<T>::SetIds)
        REGISTER_SETTER_INCLUDING_BASE_END

    protected:
        boost::optional<Pageable> m_pageable;
        boost::optional<std::vector<long>> ids;
    };



    template<class T>
    class AbstractApiSaveInput : public AbstractApiInput<T> {
    public:
        AbstractApiSaveInput() = default;

        virtual ~AbstractApiSaveInput() = default;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiSaveInput<T>)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiSaveInput<T>)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    template<class T>
    class AbstractApiSaveEntityInput : public AbstractApiSaveInput<T> {
    public:
        AbstractApiSaveEntityInput() = default;

        virtual ~AbstractApiSaveEntityInput() = default;

        virtual std::shared_ptr<AbstractBaseOutput> Process(Cruxdb::Requester *requester) = 0;

        const boost::optional<long> & GetId() const {
            return m_Id;
        }

        void SetId(boost::optional<long> & Id) {
            AbstractApiSaveEntityInput::m_Id = Id;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiSaveInput<T>)
        GETTER(AbstractApiSaveEntityInput<T>, const boost::optional<long>& , "id", &AbstractApiSaveEntityInput<T>::GetId)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiSaveInput<T>)
        SETTER(AbstractApiSaveEntityInput<T>, boost::optional<long>& , "id", &AbstractApiSaveEntityInput<T>::SetId)
        REGISTER_SETTER_INCLUDING_BASE_END

    protected:
        boost::optional<long> m_Id;
    };

} /* namespace Mocxygen */

#endif /* BASEINPUT_H_ */
