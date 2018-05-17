# GuiRent

# Cliente
- [X]	Adicionar um novo cliente. O programa deve verificar se o cliente já existe como cliente ativo ou banido, não permitindo a sua reintrodução 
- [X]	Remover um cliente (não deverá ser possível remover um cliente banido)  
- [X] Mostrar o estado de um dado cliente (quantas guitarras tem consigo, quantos alugueres fez ao todo, quantas entregas concluiu com atraso, quantas guitarras entregou danificadas)  
- [X] Listar todos os clientes ativos 
- [X] Listar clientes banidos (nome e NIF), indicando as razões pelas quais passaram para a lista negra (atraso ou guitarras danificadas) 
- [X] Banir um cliente: esta é uma funcionalidade automática que resulta da infração das regras. Não deve ser o utilizador a banir explicitamente um cliente, mas sim o programa a descobrir se um dado cliente deve ser banido. Deve ser verificado na entrega ou na tentativa de um novo aluguer. A passagem de um cliente para a lista negra implica a devolução compulsiva de guitarras que ainda tenha eventualmente alugadas. Estas guitarras ficam disponíveis para novos alugueres. 

# Guitarra
- [X]	Adicionar uma guitarra ao stock da loja 
- [X]	 Mostrar o histórico de alugueres de uma guitarra (cliente, datas de início e final do empréstimo e dias de atraso na entrega)  
- [X] Listar todas as guitarras (nome, estado, ID, preço por dia e valor) 
- [X]	Listar guitarras alugadas (nome, ID, preço por dia e valor, nome e NIF do cliente) 

# Alugueres
- [X]	Criar um aluguer para um dado cliente e guitarra, mostrando a data limite para entrega e o valor máximo previsto para o total a cobrar. Nesse processo deve ser possível visualizar todas as guitarras disponíveis (não alugadas, nem danificadas) 
- [X]	Concluir um aluguer (i.e., entrega do instrumento pelo cliente), atualizando estado do aluguer e do instrumento correspondentes, e mostrando o valor a cobrar 
- [X]	Produzir uma lista de alugueres a decorrer nesse momento, indicando para cada um: cliente, guitarra, data de início, data prevista para entrega e eventuais dias de atraso na entrega que já se verifiquem 
