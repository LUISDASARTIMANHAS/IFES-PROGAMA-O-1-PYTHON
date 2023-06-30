import random

def head():
    print("----------------------------------------------------")
    print("\t LUIS_DAS_ARTIMANHAS & PINGOBRAS S.A")
    print("\t Iniciando programa.....")
    print("----------------------------------------------------")

def data(line1,line2,line3,line4,dado1,dado2,dado3,dado4):
    print("-----------------------DADOS--------------------")
    print("\t %s : %s" %(line1,dado1))
    print("\t %s : %s" %(line2,dado2))
    print("\t %s : %s" %(line3,dado3))
    print("\t %s : %s" %(line4,dado4))
    print("----------------------------------------------------")


def copy():
    print("----------------------------------------------------")
    print("\t DEVS:")
    print("\t LUIS_DAS_ARTIMANHAS.")
    print("\t PINGOBRAS S.A")
    print("----------------------------------------------------")

def stop():
    stop = input("Deseja Finalizar A Execução? (S/N)").upper()
    print("A continuar a execução...")
    return stop


def validNota():
    nota = float(input("Insira uma Nota: "))
    while(nota < 0) or ( nota > 10):
        print("Nota Invalida!")
        nota = float(input("Insira uma Nota: "))
    return nota

def validNome():
    nome = input("Insira seu nome: ");
    nTam = len(nome)

    while(nTam <= 3 ):
        print("O nome não pode ser menor do que 3 caracteres");
        nome = input("Insira seu nome: ");
        nTam = len(nome)
    return nome

def validUser():
    user = input("Insira seu usuario: ");
    nTam = len(user)
    
    while(nTam <= 3 ):
        print("O nome não pode ser menor do que 6 caracteres");
        user = input("Insira seu usuario: ");
        nTam = len(user)
    return user

def validIdade():
    idade = int(input("Insira sua idade: "));
    while(idade <= 0) or (idade >= 50):
        print("Idade invalida.");
        idade = int(input("Insira sua idade: "));
    return idade

def validSalario():
    salario = int(input("Insira seu salario: "));
    while(salario < 0):
        print("Salario invalido.")
        salario = input("Insira Seu salario: ");
    return salario

def validSexo():
    sx = input("Insira seu sexo(F/M): ").upper();
    while (sx != "F") and (sx != "M"):
        print("Sexo invalido.")
        sx = input("Insira seu sexo(F/M): ").upper();
    return sx

def validUF():
    uf = input("Insira seu Estado Civil: ").upper();
    while (uf != "S") and (uf != "C") and (uf != "V") and (uf != "D"):
        print("Sexo invalido.")
        uf = input("Insira seu Estado Civil: ").upper();
    return uf

def validSenha():
    senha = input("Insira Sua senha: ");

    while (len(senha) < 6):
        print("A senha não pode ser menor do que 6 caracteres");
        senha = input("Insira Sua senha: ");
    return senha

def fatorial(num):
    fat = 1

    while num > 1:
        fat = fat * num
        num = num - 1
    
    return fat

def imprimirArray(placeholder,data):
    i = 0
    while i < len(data):
        print("%s %d: %.1f" % (placeholder,i, data[i]))
        i = i + 1

def validNum():
    num = int(input("Insira um número: "));
    
    while(num <= 0 ):
        print("O Número não pode ser menor do que 0!");
        num = int(input("Insira um número: "));
    return num

def validTaxa():
    tax = int(input("Insira a taxa: "));
    
    while(tax <= 0 ) or (tax >=100):
        print("A taxa não pode ser menor do que 0 ou maior que 100!");
        tax = int(input("Insira a taxa: "));
    return tax

def lancarDado():
    return random.randint(1,6)

def sequencia(stop):
    seq = 1
    while(seq <= stop):
        print(seq, end=" ")
        seq = seq + 1
    return True

def imprimirLinha(numLinha):
    cont = 0
    while(cont <= numLinha):
        print(numLinha, end=" ")
        cont = cont+1

def saldoSys(saldo,value):
    saldo = saldo + (value)
    print("Saldo Atual: %d" %saldo)
    return saldo

def somaImposto(imposto,valorCusto):
    porcentImposto = imposto/100
    taxa = valorCusto * porcentImposto
    total = valorCusto + taxa
    print("-----------------------DADOS--------------------")
    print("\t Valor do produto: %s" %valorCusto)
    print("\t Imposto: %s" %imposto)
    print("\t Taxa: %s" %taxa)
    print("\t Total a pagar: %s" %total)
    print("------------------------------------------------")

def gerarNumAleatorio(min,max):
    return random.randint(min,max)

def searchParImpVetor(vetor,vetorPar,vetorImp):
    i = 0
    while i < len(vetor):
        resto  = vetor[i] % 2
        if(resto == 0):
            vetorPar.append(vetor[i])
        else:
            vetorImp.append(vetor[i])
        i = i + 1

def gerarNumQtd(qtd,min,max, vetor):
    cont = 0
    while(cont < qtd):
        num = gerarNumAleatorio(min,max)
        vetor.append(num)
        cont = cont + 1

def intercalarVetor(input1,input2,data):
    i = 0
    while(i < len(input1)) or (i < len(input2)):
        data.append(input1[i])
        data.append(input2[i])
        i = i + 1