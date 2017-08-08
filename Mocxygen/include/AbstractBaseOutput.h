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

#ifndef BASE_OUTPUT_H
#define BASE_OUTPUT_H

#include "ApiError.h"
#include "AbstractSerializable.h"
#include "Json.h"
#include "LibCruxdb.h"

namespace Mocxygen {
    class AbstractBaseOutput : public Cmarshal::Json::AbstractSerializable {
    public:
        AbstractBaseOutput() = default;

        virtual ~AbstractBaseOutput() = default;

        virtual std::string ToString() const = 0;

        virtual std::string Name() const = 0;

        void SetError(const ApiError &error);

        ApiError GetError() const;

        web::json::value GetErrorResponse() const;

        std::string GetErrorStr() const;
        
        const web::json::value& SerializedValue() const;
        std::string SerializedStr() const;

    protected:
        ApiError m_error;

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractSerializable)
        GETTER(AbstractBaseOutput, ApiError, "error", &AbstractBaseOutput::GetError)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractSerializable)
        SETTER(AbstractBaseOutput, const ApiError&, "error", &AbstractBaseOutput::SetError)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    template<class T>
    class AbstractApiOutput : public AbstractBaseOutput {
    public:
        AbstractApiOutput() = default;

        virtual ~AbstractApiOutput() = default;

        web::json::value &Serialize() override {
            m_serializedValue = Cmarshal::Json::ToJson<T>(reinterpret_cast<const T *> (this));
            //return Cmarshal::ToJson<T>(reinterpret_cast<const T*>(this));
            return m_serializedValue;
        }

        void Deserialize(const web::json::value &jvalue) override {
            Cmarshal::Json::FromJson<T>(reinterpret_cast<T *> (this), jvalue);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractBaseOutput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractBaseOutput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T, class E>
    class AbstractApiGetOutput : public AbstractApiOutput<T> {
    private:
        using AbstractApiGetOutputTE = AbstractApiGetOutput<T, E>;

    protected:
        boost::optional<E> m_output;

    public:
        AbstractApiGetOutput() = default;

        virtual ~AbstractApiGetOutput() = default;

        const boost::optional<E> &GetOutput() const {
            return m_output;
        }

        void SetOutput(const boost::optional<E> &output) {
            AbstractApiGetOutput::m_output = output;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        GETTER(AbstractApiGetOutputTE, const boost::optional<E> &, "output", &AbstractApiGetOutputTE::GetOutput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        SETTER(AbstractApiGetOutputTE, const boost::optional<E> &, "output", &AbstractApiGetOutputTE::SetOutput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T, class E>
    class AbstractApiGetEntityOutput : public AbstractApiOutput<T> {
    private:
        using AbstractApiGetEntityOutputTE = AbstractApiGetEntityOutput<T,E>;

    protected:
        Wt::Dbo::ptr<E>  m_entity;

    public:
        AbstractApiGetEntityOutput() = default;

        virtual ~AbstractApiGetEntityOutput() = default;

        const Wt::Dbo::ptr<E> GetEntity() const {
            return m_entity;
        }

        void SetEntity(const Wt::Dbo::ptr<E> entity) {
            AbstractApiGetEntityOutput::m_entity = entity;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        GETTER(AbstractApiGetEntityOutputTE, const Wt::Dbo::ptr<E>, "entity", &AbstractApiGetEntityOutputTE::GetEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        SETTER(AbstractApiGetEntityOutputTE, const Wt::Dbo::ptr<E>, "entity", &AbstractApiGetEntityOutputTE::SetEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T, class E>
    class AbstractApiGetEntityListOutput : public AbstractApiOutput<T> {
    private:
        using AbstractApiGetEntityListOutputTE = AbstractApiGetEntityListOutput<T,E>;

        std::vector<Wt::Dbo::ptr<E>> m_entityList;
        long m_totalItem;

    public:
        AbstractApiGetEntityListOutput() = default;

        virtual ~AbstractApiGetEntityListOutput() = default;

        const std::vector<Wt::Dbo::ptr<E>> &GetEntityList() const {
            return m_entityList;
        }

        void SetEntityList(const std::vector<Wt::Dbo::ptr<E>> & entityList) {
            AbstractApiGetEntityListOutput::m_entityList = entityList;
        }


        long GetTotalItem() const {
            return m_totalItem;
        }
        void SetTotalItem(long totalItem) {
            m_totalItem = totalItem;
        }


        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        GETTER(AbstractApiGetEntityListOutputTE, const std::vector<Wt::Dbo::ptr<E>> &, "entityList", &AbstractApiGetEntityListOutputTE::GetEntityList),
        GETTER(AbstractApiGetEntityListOutputTE, long, "totalItem", &AbstractApiGetEntityListOutputTE::GetTotalItem)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        SETTER(AbstractApiGetEntityListOutputTE, const std::vector<Wt::Dbo::ptr<E>> &, "entityList", &AbstractApiGetEntityListOutputTE::SetEntityList),
        SETTER(AbstractApiGetEntityListOutputTE, long, "totalItem", &AbstractApiGetEntityListOutputTE::SetTotalItem)
        REGISTER_SETTER_INCLUDING_BASE_END
    };


    template<class T, class E>
    class AbstractApiSaveOutput : public AbstractApiOutput<T> {
    private:
        boost::optional<E> m_entity;
        using AbstractApiSaveOutputTE = AbstractApiSaveOutput<T,E>;

    public:
        AbstractApiSaveOutput() = default;

        virtual ~AbstractApiSaveOutput() = default;

        const boost::optional<E> &GetEntity() const {
            return m_entity;
        }

        void SetEntity(const boost::optional<E> &entity) {
            m_entity = entity;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        GETTER(AbstractApiSaveOutputTE, const boost::optional<E> &, "entity", &AbstractApiSaveOutputTE::GetEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        SETTER(AbstractApiSaveOutputTE, const boost::optional<E> &, "entity", &AbstractApiSaveOutputTE::SetEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

    //TODO: E should not be pointer
    template<class T, class E>
    class AbstractApiSaveEntityOutput : public AbstractApiOutput<T> {
    private:
        using AbstractApiSaveEntityOutputTE = AbstractApiSaveEntityOutput<T,E>;

    protected:
        Wt::Dbo::ptr<E> m_entity;

    public:
        AbstractApiSaveEntityOutput() = default;

        virtual ~AbstractApiSaveEntityOutput() = default;

        const Wt::Dbo::ptr<E> GetEntity() const {
            return m_entity;
        }

        void SetEntity(const Wt::Dbo::ptr<E> entity) {
            AbstractApiSaveEntityOutput::m_entity = entity;
        }

        REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        GETTER(AbstractApiSaveEntityOutputTE, const Wt::Dbo::ptr<E>, "entity", &AbstractApiSaveEntityOutputTE::GetEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<T>)
        SETTER(AbstractApiSaveEntityOutputTE, const Wt::Dbo::ptr<E>, "entity", &AbstractApiSaveEntityOutputTE::SetEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
} /* namespace Mocxygen */

#endif /* BASE_OUTPUT_H */
