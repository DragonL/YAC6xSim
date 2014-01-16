#include "common/inc/def.hpp"

BEGIN_NS

const char* op_type_name_map[] = {
  "OP_UNDEF",
  "OP_D_UNIT_32BIT_1_OR_2_SRC",
  "OP_D_UNIT_32BIT_EXT_1_OR_2_SRC",
  "OP_D_UNIT_32BIT_ADDAX_LONG_IMMED",
  "OP_D_UNIT_32BIT_LK_WD",
  "OP_D_UNIT_32BIT_LD_ST_BASIC",
  "OP_D_UNIT_32BIT_LD_ST_LONG_IMMED",
  "OP_D_UNIT_32BIT_LD_ST_DW",
  /*"OP_D_UNIT_32BIT_LD_ST_NON_ALIGN_DW",*/
  "OP_D_UNIT_16BIT_Doff4",
  "OP_D_UNIT_16BIT_Doff4DW",
  "OP_D_UNIT_16BIT_Dind",
  "OP_D_UNIT_16BIT_DindDW",
  "OP_D_UNIT_16BIT_Dinc",
  "OP_D_UNIT_16BIT_DincDW",
  "OP_D_UNIT_16BIT_Ddec",
  "OP_D_UNIT_16BIT_DdecDW",
  "OP_D_UNIT_16BIT_Dstk",
  "OP_D_UNIT_16BIT_Dx2op",
  "OP_D_UNIT_16BIT_Dx5",
  "OP_D_UNIT_16BIT_Dx5p",
  "OP_D_UNIT_16BIT_Dx1",
  "OP_D_UNIT_16BIT_Dpp",

  "OP_L_UNIT_32BIT_1_OR_2_SRC",
  "OP_L_UNIT_32BIT_UNARY",
  "OP_L_UNIT_32BIT_1_OR_2_SRC_NON_COND",
  "OP_L_UNIT_16BIT_L3",
  "OP_L_UNIT_16BIT_L3i",
  "OP_L_UNIT_16BIT_Ltbd",
  "OP_L_UNIT_16BIT_L2c",
  "OP_L_UNIT_16BIT_Lx5",
  "OP_L_UNIT_16BIT_Lx3c",
  "OP_L_UNIT_16BIT_Lx1c",
  "OP_L_UNIT_16BIT_Lx1",

  "OP_M_UNIT_32BIT_EXT_COMPOUND",
  "OP_M_UNIT_32BIT_EXT_UNARY",
  "OP_M_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND",
  "OP_M_UNIT_32BIT_MPY",
  "OP_M_UNIT_16BIT_M3",

  "OP_S_UNIT_32BIT_1_OR_2_SRC",
  "OP_S_UNIT_32BIT_ADDK",
  "OP_S_UNIT_32BIT_ADDKPC",
  "OP_S_UNIT_32BIT_EXT_1_OR_2_SRC",
  "OP_S_UNIT_32BIT_B_DISP",
  "OP_S_UNIT_32BIT_B_REG",
  "OP_S_UNIT_32BIT_B_PTR",
  "OP_S_UNIT_32BIT_BDEC_OR_BPOS",
  "OP_S_UNIT_32BIT_BNOP_DISP",
  "OP_S_UNIT_32BIT_BNOP_REG",
  "OP_S_UNIT_32BIT_CALL_NON_COND_IMMED_NOP5",
  "OP_S_UNIT_32BIT_MVK_MVKH",
  "OP_S_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND",
  "OP_S_UNIT_32BIT_UNARY",
  "OP_S_UNIT_32BIT_FIELD_OP",
  "OP_S_UNIT_16BIT_Sbs7",
  "OP_S_UNIT_16BIT_Sbu8",
  "OP_S_UNIT_16BIT_Scs10",
  "OP_S_UNIT_16BIT_Sbs7c",
  "OP_S_UNIT_16BIT_Sbu8c",
  "OP_S_UNIT_16BIT_S3",
  "OP_S_UNIT_16BIT_S3i",
  "OP_S_UNIT_16BIT_Smvk8",
  "OP_S_UNIT_16BIT_Ssh5",
  "OP_S_UNIT_16BIT_S2sh",
  "OP_S_UNIT_16BIT_Sc5",
  "OP_S_UNIT_16BIT_S2ext",
  "OP_S_UNIT_16BIT_Sx2op",
  "OP_S_UNIT_16BIT_Sx5",
  "OP_S_UNIT_16BIT_Sx1",
  "OP_S_UNIT_16BIT_Sx1b",

  "OP_LSD_UNIT_16BIT_LSDmvto",
  "OP_LSD_UNIT_16BIT_LSDmvfr",
  "OP_LSD_UNIT_16BIT_LSDx1c",
  "OP_LSD_UNIT_16BIT_LSDx1",

  "OP_N_UNIT_32BIT_DINT_RINT_SWE_SWENR",
  "OP_N_UNIT_32BIT_IDEL_NOP",
  "OP_N_UNIT_32BIT_LOOP_BUF_NON_COND",
  "OP_N_UNIT_32BIT_LOOP_BUF",
  "OP_N_UNIT_16BIT_Uspl",
  "OP_N_UNIT_16BIT_Uspldr",
  "OP_N_UNIT_16BIT_Uspk",
  "OP_N_UNIT_16BIT_Uspm",
  "OP_N_UNIT_16BIT_Unop"
};

const char* unit_type_name_map[] = {
  "None",
  "L1",
  "S1",
  "M1",
  "D1",
  "L2",
  "S2",
  "M2",
  "D2"
};


#define PUT(p, n)							\
{									\
  int nn, cc;								\
  \
  for (nn = 0; nn < n; nn++)						\
{									\
  cc = *(p+nn);							\
  *obuf++ = cc;							\
  }									\
  }

#define PAD(s, n)							\
{									\
  int nn, cc;								\
  \
  cc = *s;								\
  for (nn = n; nn > 0; nn--)						\
  *obuf++ = cc;							\
  }


#ifdef HOST_HAS_QWORD
#define HIBITL		LL(0x8000000000000000)
typedef sqword_t slargeint_t;
typedef qword_t largeint_t;
#else /* !HOST_HAS_QWORD */
#define HIBITL		0x80000000L
typedef sword_t slargeint_t;
typedef word_t largeint_t;
#endif /* HOST_HAS_QWORD */

static int
_lowdigit(slargeint_t *valptr)
{
  /* this function computes the decimal low-order digit of the number pointed
     to by valptr, and returns this digit after dividing *valptr by ten; this
     function is called ONLY to compute the low-order digit of a long whose
     high-order bit is set */

  int lowbit = (int)(*valptr & 1);
  slargeint_t value = (*valptr >> 1) & ~HIBITL;

  *valptr = value / 5;
  return (int)(value % 5 * 2 + lowbit + '0');
}

/* portable vsprintf with qword support, returns end pointer */
char *
myvsprintf(char *obuf, char *format, va_list v)
{
  static char _blanks[] = "                    ";
  static char _zeroes[] = "00000000000000000000";

  /* counts output characters */
  int count = 0;

  /* format code */
  int fcode;

  /* field width and precision */
  int width, prec;

  /* number of padding zeroes required on the left and right */
  int lzero;

  /* length of prefix */
  int prefixlength;

  /* combined length of leading zeroes, trailing zeroes, and suffix */
  int otherlength;

  /* format flags */
#define PADZERO		0x0001	/* padding zeroes requested via '0' */
#define RZERO		0x0002	/* there will be trailing zeros in output */
#define LZERO		0x0004	/* there will be leading zeroes in output */
#define DOTSEEN		0x0008	/* dot appeared in format specification */
#define LENGTH		0x0010	/* l */
  int flagword;

  /* maximum number of digits in printable number */
#define MAXDIGS		22

  /* starting and ending points for value to be printed */
  char *bp, *p;

  /* work variables */
  int k, lradix, mradix;

  /* pointer to sign, "0x", "0X", or empty */
  char *prefix;

  /* values are developed in this buffer */
  static char buf[MAXDIGS*4], buf1[MAXDIGS*4];

  /* pointer to a translate table for digits of whatever radix */
  char *tab;

  /* value being converted, if integer */
  slargeint_t val;

  /* value being converted, if floating point */
  dfloat_t fval;

  for (;;)
    {
      int n;

      while ((fcode = *format) != '\0' && fcode != '%')
	{
	  *obuf++ = fcode;
	  format++;
	  count++;
	}

      if (fcode == '\0')
	{
	  /* end of format; terminate and return */
	  *obuf = '\0';
	  return obuf;
	}


      /* % has been found, the following switch is used to parse the format
	 specification and to perform the operation specified by the format
	 letter; the program repeatedly goes back to this switch until the
	 format letter is encountered */

      width = prefixlength = otherlength = flagword = 0;
      format++;

    charswitch:
      switch (fcode = *format++)
	{
	case '0': /* means pad with leading zeros */
	  flagword |= PADZERO;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  {
	    int num = fcode - '0';
	    while (isdigit(fcode = *format))
	      {
		num = num * 10 + fcode - '0';
		format++;
	      }
	    if (flagword & DOTSEEN)
	      prec = num;
	    else
	      width = num;
	    goto charswitch;
	  }

	case '.':
	  flagword |= DOTSEEN;
	  goto charswitch;

	case 'l':
	  flagword |= LENGTH;
	  goto charswitch;

	case 'n': /* host counter */
#ifdef HOST_HAS_QWORD
	  flagword |= LENGTH;
	  /* fallthru */
#else /* !HOST_HAS_QWORD */
	  flagword |= DOTSEEN;
	  if (!width)
	    width = 12;
	  prec = 0;
	  goto process_float;
#endif /* HOST_HAS_QWORD */
	  
	case 'd':
	  /* fetch the argument to be printed */
	  if (flagword & LENGTH)
	    val = va_arg(v, slargeint_t);
	  else
	    val = (slargeint_t)va_arg(v, sword_t);

	  /* set buffer pointer to last digit */
	  p = bp = buf + MAXDIGS;

	  /* If signed conversion, make sign */
	  if (val < 0)
	    {
	      prefix = "-";
	      prefixlength = 1;
	      /* negate, checking in advance for possible overflow */
	      if (val != (slargeint_t)HIBITL)
		val = -val;
	      else
		{
		  /* number is -HIBITL; convert last digit and get pos num */
		  *--bp = _lowdigit(&val);
		}
	    }

	decimal:
	  {
	    slargeint_t qval = val;

	    if (qval <= 9)
	      *--bp = (int)qval + '0';
	    else
	      {
		do {
		  n = (int)qval;
		  qval /= 10;
		  *--bp = n - (int)qval * 10 + '0';
		}
		while (qval > 9);
		*--bp = (int)qval + '0';
	      }
	  }
	  break;

	case 'u':
	  /* fetch the argument to be printed */
	  if (flagword & LENGTH)
	    val = va_arg(v, largeint_t);
	  else
	    val = (largeint_t)va_arg(v, word_t);

	  /* set buffer pointer to last digit */
	  p = bp = buf + MAXDIGS;

	  if (val & HIBITL)
	    *--bp = _lowdigit(&val);
	  goto decimal;

	case 'o':
	  mradix = 7;
	  lradix = 2;
	  goto fixed;

	case 'p': /* target address */
	  if (sizeof(md_addr_t) > 4)
	    flagword |= LENGTH;
	  /* fallthru */

	case 'X':
	case 'x':
	  mradix = 15;
	  lradix = 3;

	fixed:
	  /* fetch the argument to be printed */
	  if (flagword & LENGTH)
	    val = va_arg(v, largeint_t);
	  else
	    val = (largeint_t)va_arg(v, word_t);

	  /* set translate table for digits */
	  tab = (fcode == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";

	  /* develop the digits of the value */
	  p = bp = buf + MAXDIGS;

	  {
	    slargeint_t qval = val;

	    if (qval == 0)
	      {
		otherlength = lzero = 1;
		flagword |= LZERO;
	      }
	    else
	      do {
		*--bp = tab[qval & mradix];
		qval = ((qval >> 1) & ~HIBITL) >> lradix;
	      } while (qval != 0);
	  }
	  break;

#ifndef HOST_HAS_QWORD
	process_float:
#endif /* !HOST_HAS_QWORD */

	case 'f':
	  if (flagword & DOTSEEN)
	    sprintf(buf1, "%%%d.%df", width, prec);
	  else if (width)
	    sprintf(buf1, "%%%df", width);
	  else
	    sprintf(buf1, "%%f");

	  /* fetch the argument to be printed */
	  fval = va_arg(v, dfloat_t);

	  /* print floating point value */
	  sprintf(buf, buf1, fval);
	  bp = buf;
	  p = bp + strlen(bp);
	  break;

	case 's':
	  bp = va_arg(v, char *);
	  if (bp == NULL)
	    bp = "(null)";
	  p = bp + strlen(bp);
	  break;

	case '%':
	  buf[0] = fcode;
	  goto c_merge;

	case 'c':
	  buf[0] = va_arg(v, int);
	c_merge:
	  p = (bp = &buf[0]) + 1;
	  break;

	default:
	  /* this is technically an error; what we do is to back up the format
             pointer to the offending char and continue with the format scan */
	  format--;
	  continue;
	}

      /* calculate number of padding blanks */
      k = (n = p - bp) + prefixlength + otherlength;
      if (width <= k)
	count += k;
      else
	{
	  count += width;

	  /* set up for padding zeroes if requested; otherwise emit padding
             blanks unless output is to be left-justified */
	  if (flagword & PADZERO)
	    {
	      if (!(flagword & LZERO))
		{
		  flagword |= LZERO;
		  lzero = width - k;
		}
	      else
		lzero += width - k;

	      /* cancel padding blanks */
	      k = width;
	    }
	  else
	    {
	      /* blanks on left if required */
	      PAD(_blanks, width - k);
	    }
	}

      /* prefix, if any */
      if (prefixlength != 0)
	{
	  PUT(prefix, prefixlength);
	}

      /* zeroes on the left */
      if (flagword & LZERO)
	{
	  PAD(_zeroes, lzero);
	}

      /* the value itself */
      if (n > 0)
	{
	  PUT(bp, n);
	}
    }
}

/* portable sprintf with qword support, returns end pointer */
char *
mysprintf(char *obuf, char *format, ...)
{
  /* vararg parameters */
  va_list v;
  va_start(v, format);

  return myvsprintf(obuf, format, v);
}

/* portable vfprintf with qword support, returns end pointer */
void myvfprintf(FILE *stream, char *format, va_list v)
{
  /* temp buffer */
  char buf[2048];

  myvsprintf(buf, format, v);
  fputs(buf, stream);
}

/* declare a fatal run-time error, calls fatal hook function */
#ifdef __GNUC__
void
_fatal(char *file, const char *func, int line, char *fmt, ...)
#else /* !__GNUC__ */
void
fatal(char *fmt, ...)
#endif /* __GNUC__ */
{
  va_list v;
  va_start(v, fmt);

  fprintf(stderr, "fatal: ");
  myvfprintf(stderr, fmt, v);
#ifdef __GNUC__
  if (verbose)
    fprintf(stderr, " [%s:%s, line %d]", func, file, line);
#endif /* __GNUC__ */
  fprintf(stderr, "\n");
  //if (hook_fn)
  //  (*hook_fn)(stderr);
  exit(1);
}

END_NS