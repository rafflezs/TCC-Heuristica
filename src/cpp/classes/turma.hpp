#ifndef _SALA_HPP
#define _SALA_HPP

class Sala {
  private:
    std::string id;
    std::string nome;
    int capacidade;
    std::string bloco;
    int list_id;
  
  public:
    void setId(const std::string &str);
    std::string getId() const;

    void setNome(const std::string &str);
    std::string getNome() const;

    void setCapacidade(const int value);
    int getCapacidade() const;

    void setbloco(const std::string &str);
    std::string getbloco() const;

    void setId(const int value);
    int getId() const;
    
}

#endif // !_SALA>_HPP