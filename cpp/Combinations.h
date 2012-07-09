// GPL Licenced code downloaded from Koders.com

#ifndef COMBINATIONS_H
#define COMBINATIONS_H
#include <vector>
#include <iostream>

// a class to iterate through m combinations out of n
class Combinations
{
   public:
      Combinations(int m, int n) : m_(m), n_(n), done_(0)
      {
         if (m_ <= n_)
         {
            combination_.resize(m_);
            for (int i = 0; i < m_; i++) combination_[i] = i;
         }
      }

      int next()
      {
         if (done_) return !done_;
         int pos = m_ - 1;
         combination_[pos]++;
         while (combination_[pos] > (n_ - m_ + pos) && !done_)
         {
            --pos;
            combination_[pos]++;
            for (int i = pos + 1; i < m_; i++)
               combination_[i] = combination_[i - 1] + 1;
            if (combination_[0] > n_ - m_) done_ = 1;
         }
         return !done_;
      }

      int operator() (int i)
      {
         if (i < m_) return combination_[i];
         return -1;
      }

      int size()
      {
         return combination_.size();
      }

      int done()
      {
         return done_;
      }

      void display()
      {
         for (int i = 0; i < m_; i++)
         {
            std::cout << combination_[i] << " ";
         }
         std::cout << std::endl;
      }

   private:
      int m_;
      int n_;
      int done_;
      std::vector<int> combination_;
};

class KnuthCombinations
{
      // Based on Algorithm 7.2.1.2T from "7.2.1.3 GENERATING ALL COMBINATIONS" of TAOCP (Fascicle 3A)
   public:
      KnuthCombinations(int t, int n) : t_(t), n_(n), done_(0)
      {
         if (t_ < n_)
         {
            c_.resize(t_ + 2);
            // Step T1. [Initialize.]
            // Note: Knuth has 1 <= j <= t
            for (int j = 1; j <= t_; j++) c(j) = j - 1;
            c(t_ + 1) = n_;
            c(t_ + 2) = 0;
            j_ = t_;
         }
      }

   private:
      void increase_c_j(int x)
      {
         // Step T6. [Increase c_j.]
         c(j_) = x;
         --j_;
      }

   public:
      bool next()
      {
         if (done_) return !done_;
         // Step T2. [Visit.]
         // Note: we assume any "visiting" has already been done at this point
         if (j_ > 0)
         {
            increase_c_j(j_);
         }
         else
         {
            // Step T3. [Easy case?]
            if (c(1) + 1 < c(2))
            {
               ++c(1);
            }
            else
            {
               j_ = 2;
               // Step T4. [Find j.]
               int x = 0;
#if 1
               bool done = false;
               while (!done)
               {
                  c(j_ - 1) = j_ - 2;
                  x = c(j_) + 1;
                  if (x == c(j_ + 1)) ++j_;
                  else done = true;
               }
#else
               c(j_ - 1) = j_ - 2;
               x = c(j_) + 1;
               while (x == c(j_ + 1)) ++j_;
#endif
               // Step T5. [Done?]
               if (j_ > t_) done_ = true;
               increase_c_j(x);
            }
         }
         return !done_;
      }

      int operator() (int i)
      {
         if (i < t_) return c_[i];
         return -1;
      }

      int size()
      {
         return (c_.size() - 2);
      }

      int done()
      {
         return done_;
      }

      void display()
      {
         for (int i = 0; i < t_; i++)
         {
            std::cout << c_[i] << " ";
         }
         std::cout << std::endl;
      }

   private:
      int t_;
      int n_;
      int j_;
      int done_;
      std::vector<int> c_;
      int& c(int j)
      {
         return c_[j - 1];
      }
};

#endif
