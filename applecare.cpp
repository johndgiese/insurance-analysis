#include <iostream>
#include <string>
#include <random>

const int max_years_in = 3;
const int apple_care_cutoff = 2;
const double phone_cost = 1000;
const double insurance_cost = 200;

std::random_device rd;
std::mt19937 rng{rd()};

int main(int argc, char** argv) {
    int liklihood_of_breaking;
    if (argc != 2) {
        return 1;
    }
    try {
        liklihood_of_breaking = std::stoi(argv[1]);
    } catch (std::invalid_argument const &e) {
        return 1;
    }

    std::uniform_int_distribution<int> broke_phone_dist{0, liklihood_of_breaking - 1};
    std::uniform_real_distribution<double> years_in_dist{0, max_years_in};

    double average_outcome_insurance = 0;
    double average_outcome_no_insurance = 0;
    int num_simulations = 10000;
    for (int i = 0; i < num_simulations; i++) {
        bool broke_phone = broke_phone_dist(rng) == 0;
        if (broke_phone) {
            double years_in = years_in_dist(rng);
            double depreciated_phone_cost = phone_cost*years_in/max_years_in;
            if (years_in > apple_care_cutoff) {
                average_outcome_no_insurance -= depreciated_phone_cost;
                average_outcome_insurance -= (insurance_cost + depreciated_phone_cost);
            } else {
                average_outcome_no_insurance -= depreciated_phone_cost;
                average_outcome_insurance -= insurance_cost;
            }
        } else {
            average_outcome_no_insurance -= 0;
            average_outcome_insurance -= insurance_cost;
        }
    }
    std::cout << "Assuming " << 100/liklihood_of_breaking << "% of people will break their phone during the 3 years" << std::endl;
    std::cout << "The average outcome without AppleCare is: " << average_outcome_no_insurance/num_simulations << std::endl;
    std::cout << "The average outcome with AppleCare is: " << average_outcome_insurance/num_simulations << std::endl;
    return 0;
}
