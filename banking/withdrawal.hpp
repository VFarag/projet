#pragma once


class Card {
    public:
        virtual int max_withdrawal() const = 0;
        virtual int max_credit() const = 0;
};

class GoldCard : public Card {
    public:
        int max_withdrawal() const override;
        int max_credit() const override;
};

class PlatiniumCard : public Card {
    public:
        int max_withdrawal() const override;
        int max_credit() const override;
};

class BlackCard : public Card {
    public:
        int max_withdrawal() const override;
        int max_credit() const override;
};



template<typename Card>
class Withdrawal {
    // "retirer de l'argent" n'a pas à changer si
    // les règles spécifiques à une carte changent.
    private:
        Card &creditcard;

    public:
        Withdrawal(Card &card);
        int operator()(int amount);
};
