#define M_EXIST CONCAT(Exist)
#define M_EVAL CONCAT(Eval)
#define M_TYPE CONCAT(Type)
#define M_CALL CONCAT(Call)

// Signature match
template<typename A>
static std::true_type M_EXIST(void (A::*)()) {
	return std::true_type();
}

// Check if the function Exist
template <typename A>
static decltype(M_EXIST(&A::FUNC)) M_EXIST(decltype(&A::FUNC), void *) {
	typedef decltype(M_EXIST(&A::FUNC)) return_type;
	return return_type();
}

// Signature doesn't match
template<typename A>
static std::false_type M_EXIST(...) {
	return std::false_type();
}

typedef decltype(M_EXIST<T>(0, 0)) M_TYPE;

// If the function exist call her
static void M_EVAL(T *t, std::true_type) {
	m_mutex.lock();
	t->FUNC();
	m_mutex.unlock();
}

// If the function doesn't exist
static void M_EVAL(...) {
	// std::cout << "T::" << M_NAME << "() not called" << std::endl;
}

static void M_EVAL(T *t) {
	M_EVAL(t, M_TYPE());
}

template<class S, typename ...Rest>
static void M_CALL(typelist<S, Rest...>, SaltyBehaviour *obj)
{
	if (dynamic_cast<S *>(obj))
		SaltyReflection<S>::M_EVAL(static_cast<S *>(obj));
	else
		return M_CALL(typelist<Rest...>(), obj);
}

template<class U>
static void M_CALL(typelist<U>, SaltyBehaviour *obj)
{
	if (dynamic_cast<U *>(obj))
		SaltyReflection<U>::M_EVAL(static_cast<U *>(obj));
}

#undef FUNC
#undef M_TYPE
#undef M_NAME
#undef M_EXIST
#undef M_EVAL
#undef M_CALL