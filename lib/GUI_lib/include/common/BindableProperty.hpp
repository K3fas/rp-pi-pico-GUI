//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BINDABLE_HPP
#define PICO_KIT_FRAMEWORK_BINDABLE_HPP

namespace rpgui::common
{
    template<typename T>
    class BindableProperty
    {
    private:
        T* _implicitValue;
        T& _value;
        
    public:
        BindableProperty() = delete;
        BindableProperty(const BindableProperty&) = delete;
        ~BindableProperty();

        BindableProperty(T& value);
        BindableProperty(const T& value);

        void SetValue(const T value);
        const T& GetValue() const;
    };

    template <typename T>
    inline BindableProperty<T>::~BindableProperty()
    {
        if(_implicitValue)
            delete _implicitValue;
    }

    template <typename T>
    inline BindableProperty<T>::BindableProperty(T &value)
        : _implicitValue(nullptr),_value(value)
    {
    }

    template <typename T>
    inline BindableProperty<T>::BindableProperty(const T&value)
        : _implicitValue(new T(value)),_value(*_implicitValue)
    {
    }

    template <typename T>
    inline void BindableProperty<T>::SetValue(const T value)
    {
        _value = value;
    }

    template <typename T>
    inline const T &BindableProperty<T>::GetValue() const
    {
        return _value;
    }

} // namespace rpgui::common

#endif  //PICO_KIT_FRAMEWORK_BINDABLE_HPP