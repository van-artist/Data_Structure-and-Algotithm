template <typename InputIt,typename Output>
void copy(InputIt start, InputIt end, Output to)
{
	while (start != end) {
		*to = *start;
		++start;
		++to;
	}
}