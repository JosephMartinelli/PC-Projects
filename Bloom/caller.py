import parallel
import sequential

exec_times = []
init_times = []

if __name__ == '__main__':
    # for i in range(10):
    #     init,exec = parallel.exec()
    #     exec_times.append(exec)
    #     init_times.append(init)
    # print(sum(init_times) / 10,sum(exec_times) / 10)

    # False positive probability
    prob = sequential.false_positive_prob(80000,6,10000)
    print("Probabilità di falsi positivi: ",prob)
    # Optimal number of hash functions
    hash_num = sequential.optimal_number_hash_func(80000,10000)
    print("Numero ottimale di funzioni hash: ",hash_num)
    # Optimal number of bits given false probabilty
    opt_m = sequential.optimal_m(10000,prob)
    print("Numero ottimale di bits: ", opt_m)
    # # Optimal number of bits per element
    # opt_k,opt_bits = sequential.optimal_bits_per_elem_and_k(prob)
    # # Given prob rate, corresponding number of hash functions
    # print("Numero ottimale di bits per elem: ", opt_m,"\nNumero ottimale di k: ",opt_k)