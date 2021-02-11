//
// Created by Grove on 2017-05-04.
//

#ifndef JIMP_EXERCISES_SERIALIZATION_H
#define JIMP_EXERCISES_SERIALIZATION_H

#include <string>
#include <vector>
#include <functional>
namespace academia {

class Serializer;

    class Serializable {
    public:
        virtual void Serialize(Serializer *ser) const =0;
    };

    class Room : public Serializable {
    public:

        enum class Type {
            COMPUTER_LAB,
            LECTURE_HALL,
            CLASS_ROOM
        };

        Room(int id_, const std::string &name_, Type type_);

        void Serialize(Serializer *ser) const override;

    private:
        int id_;
        std::string name_;
        Type type_;

    };


    class Building : public Serializable {
    public:
        Building(int id_, const std::string &name_, const std::vector<Room> &rooms_);

        void Serialize(Serializer *ser) const;
    private:
        int id_;
        std::string name_;
        std::vector<Room> rooms_;
    };

    class Serializer {
    public:

        Serializer(std::ostream *out) : out_(out) {};
        virtual void IntegerField(const std::string &field_name, int value) =0;
        virtual void DoubleField(const std::string &field_name, double value) =0;
        virtual void StringField(const std::string &field_name, const std::string &value) =0;
        virtual void BooleanField(const std::string &field_name, bool value) =0;
        virtual void SerializableField(const std::string &field_name, const academia::Serializable &value) =0;
        virtual void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) =0;
        virtual void Header(const std::string &object_name) =0;
        virtual void Footer(const std::string &object_name) =0;

    protected:
        std::ostream *out_;
    };

    class XmlSerializer : public Serializer {
    public:
        XmlSerializer(std::ostream *out) : Serializer(out){};
        void IntegerField(const std::string &field_name, int value) override ;
        void DoubleField(const std::string &field_name, double value) override;
        void StringField(const std::string &field_name, const std::string &value) override;
        void BooleanField(const std::string &field_name, bool value) override;
        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;
        void ArrayField(const std::string &field_name,
                                const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;
        void Header(const std::string &object_name) override;
        void Footer(const std::string &object_name) override;
    };

    class JsonSerializer : public Serializer {
    public:
        JsonSerializer(std::ostream *out) : Serializer(out){};
        void IntegerField(const std::string &field_name, int value) override ;
        void DoubleField(const std::string &field_name, double value) override;
        void StringField(const std::string &field_name, const std::string &value) override;
        void BooleanField(const std::string &field_name, bool value) override;
        void SerializableField(const std::string &field_name, const academia::Serializable &value) override;
        void ArrayField(const std::string &field_name,
                        const std::vector<std::reference_wrapper<const academia::Serializable>> &value) override;
        void Header(const std::string &object_name) override;
        void Footer(const std::string &object_name) override;
    };

}
#endif //JIMP_EXERCISES_SERIALIZATION_H