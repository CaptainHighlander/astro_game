#pragma once


namespace environments
{
    class Environment
    {
    public:  // Public constructors, destructor and operators
        Environment(const Environment& other) = delete;
        virtual ~Environment(void);

        Environment& operator=(const Environment& other) = delete;

    protected:  // Protected constructors and operators
        Environment(void);

    public:  // Public methods:
        virtual void update(const float delta_time) = 0;
    };
}
